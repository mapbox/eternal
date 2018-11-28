export BUILDTYPE ?= Debug
buildtype := $(shell echo "$(BUILDTYPE)" | tr "[A-Z]" "[a-z]")
export BUILDDIR ?= build/default/$(buildtype)

ifeq ($(shell uname -s), Darwin)
  export JOBS ?= $(shell sysctl -n hw.ncpu)
else ifeq ($(shell uname -s), Linux)
  export JOBS ?= $(shell grep --count processor /proc/cpuinfo)
else
  $(error Cannot determine host platform)
endif

.PHONY: all
all: $(BUILDDIR)/Makefile
	cmake --build "$(BUILDDIR)" -j $(JOBS)

.PHONY: test
test: $(BUILDDIR)/Makefile
	cmake --build "$(BUILDDIR)" -j $(JOBS) -- test-map

.PHONY: run-test
run-test: test
	"$(BUILDDIR)/test/test-map" yellow

.PHONY: benchmark
benchmark: $(BUILDDIR)/Makefile
	cmake --build "$(BUILDDIR)" -j $(JOBS) -- benchmark-map

.PHONY: run-benchmark
run-benchmark: benchmark
	"$(BUILDDIR)/test/benchmark-map"

.PRECIOUS: $(BUILDDIR)/Makefile
$(BUILDDIR)/Makefile:
	mkdir -p $(BUILDDIR)
	cmake -H. -B$(BUILDDIR) -DCMAKE_BUILD_TYPE=$(BUILDTYPE)

.PRECIOUS: build/android-%/build.ninja
build/android-%/build.ninja: CMAKE = $(shell which $(ANDROID_HOME)/cmake/*/bin/cmake)
build/android-%/build.ninja: NINJA = $(shell which $(ANDROID_HOME)/cmake/*/bin/ninja)
build/android-%/build.ninja:
	mkdir -p build/android-$*
	$(CMAKE) -H. -Bbuild/android-$* \
	    -GNinja \
	    -DCMAKE_BUILD_TYPE=$(BUILDTYPE) \
	    -DCMAKE_MAKE_PROGRAM=$(NINJA) \
	    -DCMAKE_TOOLCHAIN_FILE=$(ANDROID_HOME)/ndk-bundle/build/cmake/android.toolchain.cmake \
	    -DWITH_BENCHMARKS=OFF \
	    -DANDROID_ABI=$* \
	    -DANDROID_PLATFORM=android-14 \
	    -DANDROID_NDK=$(ANDROID_HOME)/ndk-bundle \
	    -DANDROID_TOOLCHAIN=clang \
	    -DANDROID_STL=c++_static

.PHONY: android-all
android-all: android-armeabi-v7a
android-all: android-arm64-v8a
android-all: android-x86
android-all: android-x86_64

android-%: build/android-%/build.ninja
	cmake --build  build/android-$* -j $(JOBS)

.PHONY: docker-all
docker-all: docker-linux-gcc-4.9
docker-all: docker-linux-gcc-5
docker-all: docker-linux-gcc-6
docker-all: docker-linux-gcc-7
docker-all: docker-linux-gcc-8
docker-all: docker-linux-clang-3.9
docker-all: docker-linux-clang-4
docker-all: docker-linux-clang-5
docker-all: docker-linux-clang-6
docker-all: docker-linux-clang-7

docker-linux-%:
	docker run -v `pwd`:/src --rm -e=BUILDTYPE=$(BUILDTYPE) -e=BUILDDIR=build/linux-$*/$(buildtype) -it mbgl/linux-$* make run-test run-benchmark
