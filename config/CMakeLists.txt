message(STATUS "------------Load config  details------------")
include(CMakeRC.cmake)

SET(CONF_DATA_DIR ${CMAKE_CURRENT_LIST_DIR}/)
file(GLOB_RECURSE CONF_DATA_FILES ${CMAKE_CURRENT_LIST_DIR}/conf_data/*.json)


CMRC_ADD_RESOURCE_LIBRARY(
    cmrc_config
    WHENCE ${CONF_DATA_DIR}
    NAMESPACE cmrc_config
    PREFIX cmrc_config
    ${CONF_DATA_FILES}
)
#符号隐藏防止其他插件可以读到其他插件的配置
set_target_properties(cmrc_config PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
