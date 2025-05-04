cmake_minimum_required(VERSION 3.5)

project(sample)

include_directories(
  source
)

add_executable(sample.elf
  source/main.cpp
)

target_link_libraries(sample.elf
  kernel_sys
  SceAppInstUtil
)

set(APPDIR "sample")
set(APP_VERSION "1.06")

add_custom_target(package
   DEPENDS sample.elf
   COMMAND rm -rf ${APPDIR}
   COMMAND rm -f sample.zip
   COMMAND mkdir -p ${APPDIR}
   COMMAND cp -R ${PROJECT_SOURCE_DIR}/data/* ${APPDIR}
   COMMAND cp sample.elf ${APPDIR}

   COMMAND zip -r sample.zip ${APPDIR}/
)