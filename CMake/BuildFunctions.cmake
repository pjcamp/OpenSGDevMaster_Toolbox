
#############################################################################
# print message depending on the setting of OSG_VERBOSE_BUILD_MESSAGES

FUNCTION(OSG_MSG MSG)
    IF(OSG_VERBOSE_BUILD_MESSAGES)
        MESSAGE(STATUS "${MSG}")
    ENDIF(OSG_VERBOSE_BUILD_MESSAGES)
ENDFUNCTION(OSG_MSG)

#############################################################################
# includes _OSG_FILENAME if it exists, otherwise bails with an error.

MACRO(OSG_CHECKED_INCLUDE _OSG_FILENAME)
    IF(NOT EXISTS "${_OSG_FILENAME}")
        MESSAGE(FATAL_ERROR "File \"${_OSG_FILENAME}\" not found, "
                "required by ${PROJECT_NAME}\n")
    ENDIF(NOT EXISTS "${_OSG_FILENAME}")

    INCLUDE("${_OSG_FILENAME}")
ENDMACRO(OSG_CHECKED_INCLUDE)

#############################################################################
# includes _OSG_FILENAME if it exists, otherwise just ignores it.

MACRO(OSG_OPTIONAL_INCLUDE _OSG_FILENAME)
    IF(EXISTS "${_OSG_FILENAME}")
        INCLUDE("${_OSG_FILENAME}")
    ENDIF(EXISTS "${_OSG_FILENAME}")
ENDMACRO(OSG_OPTIONAL_INCLUDE)


#############################################################################
# given a list of OpenSG libraries (BASELIST) it determines the full list of
# OpenSG libs they depend upon (OUTDEPLIST) and any dependencies that could
# not be found (OUTDEPMISSINGLIST).
# Useful to get all the include dirs needed by a lib during the build.

FUNCTION(OSG_GET_ALL_DEP_OSG_LIB BASELIST OUTDEPLIST OUTDEPMISSINGLIST)

    SET(_DEPLIST        ${BASELIST})
    SET(_DEPLISTNEW                )
    SET(_DEPMISSINGLIST            )

    # CMake has no do{ }while, duplicate the while loop body once
    # outside the while loop:

    FOREACH(DEP ${_DEPLIST})
        SET(DEPFILE "${CMAKE_BINARY_DIR}/${DEP}.cmake")

        IF(NOT EXISTS "${DEPFILE}")
            LIST(APPEND _DEPMISSINGLIST ${DEP})
        ENDIF(NOT EXISTS "${DEPFILE}")

        OSG_OPTIONAL_INCLUDE("${DEPFILE}")

        LIST(APPEND _DEPLISTNEW ${DEP})
        LIST(APPEND _DEPLISTNEW ${${DEP}_DEP_OSG_LIB})

        LIST(SORT              _DEPLISTNEW)
        LIST(REMOVE_DUPLICATES _DEPLISTNEW)
    ENDFOREACH(DEP)

    LIST(LENGTH _DEPLIST    _DEPLISTLEN   )
    LIST(LENGTH _DEPLISTNEW _DEPLISTNEWLEN)

    #MESSAGE("_DEPLIST   : ${_DEPLIST}"   )
    #MESSAGE("_DEPLISTNEW: ${_DEPLISTNEW}")

    # keep iterating as long as new elements are added
    WHILE(${_DEPLISTNEWLEN} GREATER ${_DEPLISTLEN})

        SET(_DEPLIST    ${_DEPLISTNEW})
        SET(_DEPLISTNEW               )

        FOREACH(DEP ${_DEPLIST})
            SET(DEPFILE "${CMAKE_BINARY_DIR}/${DEP}.cmake")

            IF(NOT EXISTS "${DEPFILE}")
                LIST(APPEND _DEPMISSINGLIST ${DEP})
            ENDIF(NOT EXISTS "${DEPFILE}")

            OSG_OPTIONAL_INCLUDE("${DEPFILE}")

            LIST(APPEND _DEPLISTNEW ${DEP}               )
            LIST(APPEND _DEPLISTNEW ${${DEP}_DEP_OSG_LIB})

            LIST(SORT              _DEPLISTNEW)
            LIST(REMOVE_DUPLICATES _DEPLISTNEW)
        ENDFOREACH(DEP)

        #MESSAGE("_DEPLIST   : ${_DEPLIST}"   )
        #MESSAGE("_DEPLISTNEW: ${_DEPLISTNEW}")

        LIST(LENGTH _DEPLIST    _DEPLISTLEN   )
        LIST(LENGTH _DEPLISTNEW _DEPLISTNEWLEN)
    ENDWHILE(${_DEPLISTNEWLEN} GREATER ${_DEPLISTLEN})

    IF(_DEPMISSINGLIST)
        LIST(REMOVE_DUPLICATES _DEPMISSINGLIST)
    ENDIF(_DEPMISSINGLIST)

    SET(${OUTDEPLIST}        "${_DEPLISTNEW}"     PARENT_SCOPE)
    SET(${OUTDEPMISSINGLIST} "${_DEPMISSINGLIST}" PARENT_SCOPE)

ENDFUNCTION(OSG_GET_ALL_DEP_OSG_LIB)

#############################################################################
# register project with build

MACRO(OSG_ADD_PROJECT PNAME)
    PROJECT(${PNAME})
    IF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        OPTION(OSGBUILD_${PROJECT_NAME} "Build the ${PROJECT_NAME} library" ON)
        SET(${PROJECT_NAME}_SOURCE_GROUPS "" CACHE INTERNAL "" FORCE)
    ENDIF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
ENDMACRO(OSG_ADD_PROJECT)

#############################################################################
# select the current project as the one settings are added to

MACRO(OSG_SELECT_PROJECT)

    IF(OSGBUILD_${PROJECT_NAME})
        MESSAGE(STATUS "Processing ${PROJECT_NAME}")
    ELSE(OSGBUILD_${PROJECT_NAME})
        OSG_MSG("Skipping ${PROJECT_NAME}")
        RETURN()
    ENDIF(OSGBUILD_${PROJECT_NAME})

    SET_DIRECTORY_PROPERTIES(PROPERTIES CLEAN_NO_CUSTOM TRUE)

    SET(${PROJECT_NAME}_BUILD_FILE
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake")
    SET(${PROJECT_NAME}_CONFIG_FILE
        "${CMAKE_BINARY_DIR}/bin/osg2-config.part2.tmp")

    # write header
    IF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        FILE(WRITE ${${PROJECT_NAME}_BUILD_FILE}
            "# ${PROJECT_NAME}.cmake -- auto generated\n\n")

        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_SRC ${OSG_ADD_GLOBAL_SRC} ${${PROJECT_NAME}_ADD_SRC})\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_HDR)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_INL)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_INS)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_FCD)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_LL)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_YY)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "SET(${PROJECT_NAME}_MOC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_UNITTEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_TEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_INC)\n\n")
    ENDIF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    # clear dependency variables
    SET(${PROJECT_NAME}_DEP_OSG_LIB)
    SET(${PROJECT_NAME}_DEP_TEST_OSG_LIB)
    SET(${PROJECT_NAME}_DEP_TEST_OSG_EEX_LIB)
    SET(${PROJECT_NAME}_DEP_UNITTEST_OSG_LIB)

    SET(${PROJECT_NAME}_DEP_LIB)
    SET(${PROJECT_NAME}_DEP_LIBDIR)
    SET(${PROJECT_NAME}_DEP_INCDIR)
    SET(${PROJECT_NAME}_DEP_DEFS)

    SET(${PROJECT_NAME}_DEP_TEST_LIB)
    SET(${PROJECT_NAME}_DEP_TEST_LIBDIR)
    SET(${PROJECT_NAME}_DEP_TEST_INCDIR)
    SET(${PROJECT_NAME}_DEP_TEST_DEFS)

    SET(${PROJECT_NAME}_DEP_UNITTEST_LIB)
    SET(${PROJECT_NAME}_DEP_UNITTEST_LIBDIR)
    SET(${PROJECT_NAME}_DEP_UNITTEST_INCDIR)

    SET(${PROJECT_NAME}_DEP_ADD_INCDIR)

    SET(${PROJECT_NAME}_EXCL_FILES)

    SET(${PROJECT_NAME}_BASE_DIR)

    SET(${PROJECT_NAME}_SRC_PATTERNS)
    SET(${PROJECT_NAME}_HDR_PATTERNS)
    SET(${PROJECT_NAME}_INL_PATTERNS)

    SET(${PROJECT_NAME}_SUFFIX)

    SET(${PROJECT_NAME}_NO_DOC)

ENDMACRO(OSG_SELECT_PROJECT)

#############################################################################
# Extract separate libs and paths from a list of files.
#
# cmake stores libraries as full paths to the library file, this splits
# this form into a library (suitable for use on the linker command line) and
# the path where that library can be found.
FUNCTION(OSG_EXTRACT_LIB_AND_LIBDIR INLIBS OUTLIBS OUTLIBDIRS)

    FOREACH(INLIB ${INLIBS})
        GET_FILENAME_COMPONENT(INLIB_LIB    ${INLIB} NAME)
        GET_FILENAME_COMPONENT(INLIB_LIBDIR ${INLIB} PATH)

        STRING(REPLACE "${CMAKE_SHARED_LIBRARY_PREFIX}" "" INLIB_LIB ${INLIB_LIB})
        STRING(REPLACE "${CMAKE_SHARED_LIBRARY_SUFFIX}" "" INLIB_LIB ${INLIB_LIB})

        LIST(APPEND OLIBS ${INLIB_LIB})
        LIST(APPEND OLIBDIRS ${INLIB_LIBDIR})
    ENDFOREACH(INLIB)

    SET(${OUTLIBS} ${OLIBS} PARENT_SCOPE)
    SET(${OUTLIBDIRS} ${OLIBDIRS} PARENT_SCOPE)

ENDFUNCTION(OSG_EXTRACT_LIB_AND_LIBDIR)

FUNCTION(OSG_EXTRACT_LIBDIR INLIBDIRS OUTLIBDIRS)

    FOREACH(INLIBDIR ${INLIBDIRS})
        LIST(APPEND OLIBDIRS ${INLIBDIR})
    ENDFOREACH(INLIBDIR)

    SET(${OUTLIBDIRS} ${OLIBDIRS} PARENT_SCOPE)
ENDFUNCTION(OSG_EXTRACT_LIBDIR)

FUNCTION(OSG_EXTRACT_INCDIR ININCDIRS OUTINCDIRS)

    FOREACH(ININCDIR ${ININCDIRS})
        LIST(APPEND OINCDIRS ${ININCDIR})
    ENDFOREACH(ININCDIR)

    SET(${OUTINCDIRS} ${OINCDIRS} PARENT_SCOPE)
ENDFUNCTION(OSG_EXTRACT_INCDIR)

#############################################################################
# write the dependecy variables to the ${${PROJECT_NAME}_BUILD_FILE} file
# for use during the build and to
# ${${PROJECT_NAME}_CONFIG_FILE} for constructing osg2-config

FUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    #########################################
    # store dependencies for the build

    # dependencies - OpenSG
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_OSG_LIB ${${PROJECT_NAME}_DEP_OSG_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_OSG_LIB ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_OSG_EEX_LIB ${${PROJECT_NAME}_DEP_TEST_OSG_EEX_LIB})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_UNITTEST_OSG_LIB ${${PROJECT_NAME}_DEP_UNITTEST_OSG_LIB})\n\n")

    # dependencies - external
    IF(OSG_GLOBAL_LIB)
      LIST(APPEND ${PROJECT_NAME}_DEP_LIB ${OSG_GLOBAL_LIB})
    ENDIF(OSG_GLOBAL_LIB)
    IF(${PROJECT_NAME}_ADD_LIB)
      LIST(APPEND ${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_ADD_LIB})
    ENDIF(${PROJECT_NAME}_ADD_LIB)

    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_INCDIR ${${PROJECT_NAME}_DEP_INCDIR})\n\n")

    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIBDIR ${${PROJECT_NAME}_DEP_TEST_LIBDIR})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR})\n\n")

    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_UNITTEST_LIB ${${PROJECT_NAME}_DEP_UNITTEST_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_UNITTEST_LIBDIR ${${PROJECT_NAME}_DEP_UNITTEST_LIBDIR})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_UNITTEST_INCDIR ${${PROJECT_NAME}_DEP_UNITTEST_INCDIR})\n\n")

    # dependencies - additional
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_ADD_INCDIR ${${PROJECT_NAME}_DEP_ADD_INCDIR})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_DEFS ${${PROJECT_NAME}_DEP_DEFS})\n\n")

    # for external projects

    FILE(APPEND "${CMAKE_BINARY_DIR}/OpenSGExtDep.cmake"
        "SET(${PROJECT_NAME}_DEP_OSG_LIB ${${PROJECT_NAME}_DEP_OSG_LIB})\n\n")

    FILE(APPEND "${CMAKE_BINARY_DIR}/OpenSGExtDep.cmake"
        "SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB})\n\n")

    FILE(APPEND "${CMAKE_BINARY_DIR}/OpenSGExtDep.cmake"
        "LIST(APPEND STORED_PROJECTS ${PROJECT_NAME})\n\n")



    #########################################################################
    # Store dependencies for osg2-config.
    # This is a bit lengthy as it writes a python dictionary

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "############################################################\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "## Dependecies for ${PROJECT_NAME}\n\n")

    # OpenSG libraries this lib depends on
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "\"${PROJECT_NAME}\" : {\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_osg_lib\"  :  [")

    FOREACH(DEPOSGLIB ${${PROJECT_NAME}_DEP_OSG_LIB})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${DEPOSGLIB}\", ")
    ENDFOREACH(DEPOSGLIB)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    # global dependencies
    FOREACH(DEPLIB ${OSG_GLOBAL_DEP_LIBS})
        OSG_EXTRACT_LIB_AND_LIBDIR("${${DEPLIB}}" LIBS LIBDIRS)

        FOREACH(LIB ${LIBS})
            # if the lib is an import target, get the location and
            # split that into library name and path

            IF(TARGET ${LIB})
                GET_TARGET_PROPERTY(_LIB_LOCATION ${LIB} IMPORTED_LOCATION)

                OSG_EXTRACT_LIB_AND_LIBDIR("${_LIB_LOCATION}" _LIBS _LIBDIRS)

                LIST(APPEND DEPLIBS    ${_LIBS})
                LIST(APPEND DEPLIBDIRS ${_LIBDIRS})
            ELSE(TARGET ${LIB})
                LIST(APPEND DEPLIBS ${LIB})
            ENDIF(TARGET ${LIB})
        ENDFOREACH(LIB)

        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIB)

    FOREACH(DEPLIBDIR ${OSG_GLOBAL_DEP_LIBDIR})
        OSG_EXTRACT_LIBDIR("${${DEPLIBDIR}}" LIBDIRS)

        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIBDIR)

    FOREACH(DEPINCDIR ${OSG_GLOBAL_DEP_INCDIR})
        OSG_EXTRACT_INCDIR("${${DEPINCDIR}}" INCDIRS)

        LIST(APPEND DEPINCDIRS ${INCDIRS})
    ENDFOREACH(DEPINCDIR)

    # External libraries this lib depends on
    # we build lists of libs, libdirs and incdirs then write them
    FOREACH(DEPLIB ${${PROJECT_NAME}_DEP_LIB})
        OSG_EXTRACT_LIB_AND_LIBDIR("${${DEPLIB}}" LIBS LIBDIRS)

        FOREACH(LIB ${LIBS})
            # if the lib is an import target, get the location and
            # split that into library name and path

            IF(TARGET ${LIB})
                GET_TARGET_PROPERTY(_LIB_LOCATION ${LIB} IMPORTED_LOCATION)

                OSG_EXTRACT_LIB_AND_LIBDIR("${_LIB_LOCATION}" _LIBS _LIBDIRS)

                LIST(APPEND DEPLIBS    ${_LIBS})
                LIST(APPEND DEPLIBDIRS ${_LIBDIRS})
            ELSE(TARGET ${LIB})
                LIST(APPEND DEPLIBS ${LIB})
            ENDIF(TARGET ${LIB})
        ENDFOREACH(LIB)

        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIB)

    FOREACH(DEPLIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_EXTRACT_LIBDIR("${${DEPLIBDIR}}" LIBDIRS)

        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIBDIR)

    FOREACH(DEPINCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_EXTRACT_INCDIR("${${DEPINCDIR}}" INCDIRS)

        LIST(APPEND DEPINCDIRS ${INCDIRS})
    ENDFOREACH(DEPINCDIR)

    IF(DEPLIBS)
        LIST(REMOVE_DUPLICATES DEPLIBS)
    ENDIF(DEPLIBS)

    IF(DEPLIBDIRS)
        LIST(REMOVE_DUPLICATES DEPLIBDIRS)
    ENDIF(DEPLIBDIRS)

    IF(DEPINCDIRS)
        LIST(REMOVE_DUPLICATES DEPINCDIRS)
    ENDIF(DEPINCDIRS)

    IF(DEPLIBS OR DEPLIBDIRS OR DEPINCDIRS)
        OSG_MSG("   DEPLIBS: ${DEPLIBS}")
        OSG_MSG("   DEPLIBDIRS: ${DEPLIBDIRS}")
        OSG_MSG("   DEPINCDIRS: ${DEPINCDIRS}")
    ENDIF(DEPLIBS OR DEPLIBDIRS OR DEPINCDIRS)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_lib\"  :  [")

    FOREACH(LIB ${DEPLIBS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${LIB}\", ")
    ENDFOREACH(LIB)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_lib_dir\"  :  [")

    FOREACH(LIBDIR ${DEPLIBDIRS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${LIBDIR}\", ")
    ENDFOREACH(LIBDIR)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_inc_dir\"  :  [")

    FOREACH(INCDIR ${DEPINCDIRS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${INCDIR}\", ")
    ENDFOREACH(INCDIR)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "},\n")

ENDFUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)


#############################################################################
# add directory DIRNAME to current project

FUNCTION(OSG_ADD_DIRECTORY DIRNAME)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    OSG_MSG("Adding directory: ${DIRNAME}")

    SET(_OSG_ADD_SRC_LOOKUP)
    SET(_OSG_ADD_HDR_LOOKUP)
    SET(_OSG_ADD_INL_LOOKUP)
    
    IF(EXISTS "${CMAKE_SOURCE_DIR}/${DIRNAME}")
        SET(_OSG_CURR_DIRNAME "${CMAKE_SOURCE_DIR}/${DIRNAME}")

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_SRC_PATTERNS})
          LIST(APPEND _OSG_ADD_SRC_LOOKUP "${CMAKE_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_HDR_PATTERNS})
          LIST(APPEND _OSG_ADD_HDR_LOOKUP "${CMAKE_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_INL_PATTERNS})
          LIST(APPEND _OSG_ADD_INL_LOOKUP "${CMAKE_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FILE(GLOB LOCAL_SRC          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.cpp"
                                     "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.mm"
                                      ${_OSG_ADD_SRC_LOOKUP}                )
        FILE(GLOB LOCAL_HDR          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.h"
                                      ${_OSG_ADD_HDR_LOOKUP}               )
        FILE(GLOB LOCAL_INL          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.inl"
                                      ${_OSG_ADD_INL_LOOKUP}                 )
        FILE(GLOB LOCAL_INS          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ins")
        FILE(GLOB LOCAL_FCD          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.fcd")
        FILE(GLOB LOCAL_LL           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ll")
        FILE(GLOB LOCAL_YY           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.yy")
        FILE(GLOB LOCAL_MOC          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*_qt.h")
        FILE(GLOB LOCAL_UNITTEST_SRC "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*Test.cpp")
        FILE(GLOB LOCAL_TEST_SRC     "${CMAKE_SOURCE_DIR}/${DIRNAME}/test*.cpp"
                                     "${CMAKE_SOURCE_DIR}/${DIRNAME}/test*.mm")
        FILE(GLOB BASE_MM            "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*Base.mm")
    ELSEIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}")
        SET(_OSG_CURR_DIRNAME "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}")

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_SRC_PATTERNS})
          LIST(APPEND _OSG_ADD_SRC_LOOKUP "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_HDR_PATTERNS})
          LIST(APPEND _OSG_ADD_HDR_LOOKUP "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_INL_PATTERNS})
          LIST(APPEND _OSG_ADD_INL_LOOKUP "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FILE(GLOB LOCAL_SRC          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.cpp"
                                     "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.mm"
                                      ${_OSG_ADD_SRC_LOOKUP}                        )
        FILE(GLOB LOCAL_HDR          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.h"
                                     ${_OSG_ADD_HDR_LOOKUP}                        )
        FILE(GLOB LOCAL_INL          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.inl"
                                     ${_OSG_ADD_INL_LOOKUP}                          )
        FILE(GLOB LOCAL_INS          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.ins")
        FILE(GLOB LOCAL_FCD          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.fcd")
        FILE(GLOB LOCAL_LL           "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.ll")
        FILE(GLOB LOCAL_YY           "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*.yy")
        FILE(GLOB LOCAL_MOC          "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*_qt.h")
        FILE(GLOB LOCAL_UNITTEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*Test.cpp")
        FILE(GLOB LOCAL_TEST_SRC     "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/test*.cpp"
                                     "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/test*.mm")
        FILE(GLOB BASE_MM            "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}/OSG*Base.mm")
    ELSE()
        SET(_OSG_CURR_DIRNAME "${DIRNAME}")

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_SRC_PATTERNS})
          LIST(APPEND _OSG_ADD_SRC_LOOKUP "${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_HDR_PATTERNS})
          LIST(APPEND _OSG_ADD_HDR_LOOKUP "${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        FOREACH(_OSG_FILE_PATTERN ${${PROJECT_NAME}_INL_PATTERNS})
          LIST(APPEND _OSG_ADD_INL_LOOKUP "${DIRNAME}/${_OSG_FILE_PATTERN}")
        ENDFOREACH()

        # Guess it's an absolute dir we got as the rel one is not there
        FILE(GLOB LOCAL_SRC          "${DIRNAME}/OSG*.cpp" 
                                     "${DIRNAME}/OSG*.mm"
                                      ${_OSG_ADD_SRC_LOOKUP})
        FILE(GLOB LOCAL_HDR          "${DIRNAME}/OSG*.h"
                                      ${_OSG_ADD_HDR_LOOKUP})
        FILE(GLOB LOCAL_INL          "${DIRNAME}/OSG*.inl"
                                      ${_OSG_ADD_INL_LOOKUP})
        FILE(GLOB LOCAL_INS          "${DIRNAME}/OSG*.ins")
        FILE(GLOB LOCAL_FCD          "${DIRNAME}/OSG*.fcd")
        FILE(GLOB LOCAL_LL           "${DIRNAME}/OSG*.ll")
        FILE(GLOB LOCAL_YY           "${DIRNAME}/OSG*.yy")
        FILE(GLOB LOCAL_MOC          "${DIRNAME}/OSG*_qt.h")
        FILE(GLOB LOCAL_UNITTEST_SRC "${DIRNAME}/OSG*Test.cpp")
        FILE(GLOB LOCAL_TEST_SRC     "${DIRNAME}/test*.cpp" "${DIRNAME}/test*.mm")
        FILE(GLOB BASE_MM            "${DIRNAME}/OSG*Base.mm")
    ENDIF()

    IF(BASE_MM)
        FOREACH(BaseMMFile ${BASE_MM})
        STRING(REGEX REPLACE mm$ cpp BaseMMFileCPP ${BaseMMFile})
        LIST(APPEND BASE_MM_CPP ${BaseMMFileCPP})
    ENDFOREACH()
    ENDIF(BASE_MM)

    IF(BASE_MM_CPP)
        LIST(REMOVE_ITEM LOCAL_SRC ${BASE_MM_CPP})
    ENDIF(BASE_MM_CPP)

    IF(${PROJECT_NAME}_EXCL_FILES)
        LIST(REMOVE_ITEM LOCAL_SRC          ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_HDR          ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_INL          ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_INS          ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_FCD          ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_LL           ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_YY           ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_UNITTEST_SRC ${${PROJECT_NAME}_EXCL_FILES})
        LIST(REMOVE_ITEM LOCAL_TEST_SRC     ${${PROJECT_NAME}_EXCL_FILES})
    ENDIF(${PROJECT_NAME}_EXCL_FILES)

    # filter unittest sources out of library sources
    IF(LOCAL_UNITTEST_SRC)
        LIST(REMOVE_ITEM LOCAL_SRC ${LOCAL_UNITTEST_SRC})
    ENDIF(LOCAL_UNITTEST_SRC)

    # store file lists
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE} "# File lists for ${DIRNAME}\n\n")

    # library sources
    IF(LOCAL_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_SRC \"${LOCAL_SRC}\")\n\n")
    ENDIF(LOCAL_SRC)

    IF(LOCAL_HDR)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_HDR \"${LOCAL_HDR}\")\n\n")
    ENDIF(LOCAL_HDR)

    IF(LOCAL_INL)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INL \"${LOCAL_INL}\")\n\n")
    ENDIF(LOCAL_INL)

    IF(LOCAL_INS)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INS \"${LOCAL_INS}\")\n\n")
    ENDIF(LOCAL_INS)

    IF(LOCAL_FCD)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_FCD \"${LOCAL_FCD}\")\n\n")
    ENDIF(LOCAL_FCD)

    IF(LOCAL_LL)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_LL \"${LOCAL_LL}\")\n\n")
    ENDIF(LOCAL_LL)

    IF(LOCAL_YY)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_YY \"${LOCAL_YY}\")\n\n")
    ENDIF(LOCAL_YY)

    IF(LOCAL_MOC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_MOC \"${LOCAL_MOC}\")\n\n")
    ENDIF(LOCAL_MOC)

    IF(NOT ${PROJECT_NAME}_BASE_DIR)
      # Add the source files to the source group
      #Strip the path down to a relative one
      IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}")
        FILE(RELATIVE_PATH THE_SOURCE_GROUP
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME})
      ELSEIF(EXISTS "${CMAKE_SOURCE_DIR}/${DIRNAME}")
        FILE(RELATIVE_PATH THE_SOURCE_GROUP
                           ${CMAKE_SOURCE_DIR}/Source
                           ${CMAKE_SOURCE_DIR}/${DIRNAME})
      ELSE()
        FILE(RELATIVE_PATH THE_SOURCE_GROUP
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${DIRNAME})
      ENDIF()
    ELSE()
        FILE(RELATIVE_PATH THE_SOURCE_GROUP
                           ${${PROJECT_NAME}_BASE_DIR}/
                           ${_OSG_CURR_DIRNAME})
    ENDIF()

    IF(THE_SOURCE_GROUP)
         STRING(REPLACE "/" "\\" THE_SOURCE_GROUP ${THE_SOURCE_GROUP})

        LIST(APPEND ${PROJECT_NAME}_SOURCE_GROUPS ${THE_SOURCE_GROUP})
        SET(${PROJECT_NAME}_SOURCE_GROUPS ${${PROJECT_NAME}_SOURCE_GROUPS}
                                          CACHE INTERNAL "" FORCE)
    
        STRING(REPLACE "\\" "_" THE_SOURCE_GROUP ${THE_SOURCE_GROUP})
        LIST(APPEND ${PROJECT_NAME}_SOURCE_GROUP_${THE_SOURCE_GROUP}
                    ${LOCAL_SRC}
                    ${LOCAL_HDR}
                    ${LOCAL_INL}
                    ${LOCAL_INS}
                    ${LOCAL_FCD}
                    ${LOCAL_LL}
                    ${LOCAL_YY}
                    ${LOCAL_MOC})
    
        SET(${PROJECT_NAME}_SOURCE_GROUP_${THE_SOURCE_GROUP}
              ${${PROJECT_NAME}_SOURCE_GROUP_${THE_SOURCE_GROUP}}
              CACHE INTERNAL "" FORCE)
    ENDIF(THE_SOURCE_GROUP)

    # unittests
    IF(LOCAL_UNITTEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "LIST(APPEND ${PROJECT_NAME}_UNITTEST_SRC \"${LOCAL_UNITTEST_SRC}\")\n\n")
    ENDIF(LOCAL_UNITTEST_SRC)

    # tests
    IF(LOCAL_TEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_TEST_SRC \"${LOCAL_TEST_SRC}\")\n\n")
    ENDIF(LOCAL_TEST_SRC)

    IF(EXISTS "${CMAKE_SOURCE_DIR}/${DIRNAME}")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_SOURCE_DIR}/${DIRNAME}\")\n\n")
    ELSEIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_CURRENT_SOURCE_DIR}/${DIRNAME}\")\n\n")
    ELSE()
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INC \"${DIRNAME}\")\n\n")
    ENDIF()
ENDFUNCTION(OSG_ADD_DIRECTORY)


#############################################################################
# perform default actions for pass OSGSETUP

FUNCTION(OSG_SETUP_LIBRARY_BUILD PROJ_DEFINE)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")

    IF(${PROJECT_NAME}_NO_LIB)
        RETURN()
    ENDIF()

    # read file lists
    OSG_CHECKED_INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

    #####
    # FCD
    #####

    IF(OSG_ENABLE_FCD2CODE AND PYTHONINTERP_FOUND)

        FOREACH(FCDFile ${${PROJECT_NAME}_FCD})
            GET_FILENAME_COMPONENT(FCDBase ${FCDFile} NAME_WE)
            GET_FILENAME_COMPONENT(FCDDir  ${FCDFile} PATH)

            SET(FCDBaseHdr "${FCDBase}Base.h")
            SET(FCDBaseCpp "${FCDBase}Base.cpp")
            SET(FCDBaseInl "${FCDBase}Base.inl")
            SET(FCDBaseFld "${FCDBase}Fields.h")

            SET(FCDClassHdr "${FCDBase}.h")
            SET(FCDClassCpp "${FCDBase}.cpp")
            SET(FCDClassInl "${FCDBase}.inl")

            IF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseHdr})
                SET(${PROJECT_NAME}_INL ${${PROJECT_NAME}_INL} ${FCDDir}/${FCDBaseInl})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseFld})

                IF(NOT EXISTS ${FCDDir}/${FCDClassHdr})
                    SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${FCDDir}/${FCDClassCpp})
                    SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDClassHdr})
                    SET(${PROJECT_NAME}_INL ${${PROJECT_NAME}_INL} ${FCDDir}/${FCDClassInl})

                    SET(FCD_TMP_OUT ${FCDDir}/${FCDClassCpp}
                                    ${FCDDir}/${FCDClassHdr}
                                    ${FCDDir}/${FCDClassInl})
                ENDIF(NOT EXISTS ${FCDDir}/${FCDClassHdr})
            ENDIF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})

            SET(FCDBaseDir ${CMAKE_SOURCE_DIR}/Tools/fcd2code)
            SET(FCDCommand ${CMAKE_SOURCE_DIR}/Tools/fcd2code/fcd2code)
            SET(FCDRoot -r ${CMAKE_SOURCE_DIR})
            SET(FCDTemp "")

            SET(FCDPath ${CMAKE_SOURCE_DIR}/Tools/fcd2code)

            IF(NOT EXISTS FCDPath AND OpenSG_DIR) #external setup
              SET(FCDBaseDir ${OpenSG_DIR}/bin/fcd2code)

              SET(FCDCommand ${OpenSG_DIR}/bin/fcd2code/fcd2code)

              SET(FCDRoot "")
              SET(FCDTemp -t ${FCDBaseDir})
            ENDIF(NOT EXISTS FCDPath AND OpenSG_DIR)

            IF(NOT EXISTS ${FCDDir}/${FCDClassHdr} AND
               NOT EXISTS ${FCDDir}/${FCDClassCpp} AND
               NOT EXISTS ${FCDDir}/${FCDClassInl} AND
               OSG_FCD2CODE_WRITE_CLASS              )

               SET(_OSG_IGNORE_CLASSWRITE -1)

               IF(OSG_IGNORE_CLASSBUILD)
                 LIST(FIND OSG_IGNORE_CLASSBUILD ${FCDBase} _OSG_IGNORE_CLASSWRITE)
               ENDIF(OSG_IGNORE_CLASSBUILD)

               IF(_OSG_IGNORE_CLASSWRITE EQUAL -1)
                 MESSAGE(STATUS "writing ${FCDDir}/${FCDClassHdr} ${FCDDir}/${FCDClassCpp} ${FCDDir}/${FCDClassInl}")

                 EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} ${FCDCommand} -c -f -d ${FCDFile} -p ${FCDDir} ${FCDRoot} ${FCDTemp})
               ENDIF(_OSG_IGNORE_CLASSWRITE EQUAL -1)

            ENDIF()

            ADD_CUSTOM_COMMAND(
                OUTPUT ${FCDDir}/${FCDBaseHdr}
                       ${FCDDir}/${FCDBaseCpp}
                       ${FCDDir}/${FCDBaseInl}
                       ${FCDDir}/${FCDBaseFld}
                       ${FCD_TMP_OUT}
                COMMAND ${PYTHON_EXECUTABLE} ${FCDCommand} -c -b -d ${FCDFile} -p ${FCDDir} ${FCDRoot} ${FCDTemp}
                MAIN_DEPENDENCY ${FCDFile}
                DEPENDS ${FCDBaseDir}/TemplateFieldContainerBase_h.txt
                        ${FCDBaseDir}/TemplateFieldContainerBase_inl.txt
                        ${FCDBaseDir}/TemplateFieldContainerBase_cpp.txt
                        ${FCDBaseDir}/TemplateFieldContainerFields_h.txt)

            SET(FCD_TMP_OUT )
        ENDFOREACH(FCDFile)

    ENDIF(OSG_ENABLE_FCD2CODE AND PYTHONINTERP_FOUND)

    ############
    # Qt4
    ############

    IF(${PROJECT_NAME} STREQUAL "OSGWindowQT4")
        # Here only the OSG_WITH_QT define is passes to qt moc.
        SET(moc_flags -DOSG_WITH_QT)

        SET(${PROJECT_NAME}_INC ${${PROJECT_NAME}_INC} ${CMAKE_CURRENT_BINARY_DIR})

        FOREACH(MOCFile ${${PROJECT_NAME}_MOC})
            GET_FILENAME_COMPONENT(MOCFile ${MOCFile} ABSOLUTE)
            QT4_MAKE_OUTPUT_FILE(${MOCFile} moc_ cpp MOCOutFile)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${MOCOutFile}
                COMMAND ${QT_MOC_EXECUTABLE}
                ARGS ${moc_flags} ${moc_options} -o ${MOCOutFile} ${MOCFile}
                DEPENDS ${MOCFile})
            LIST(APPEND ${PROJECT_NAME}_SRC ${MOCOutFile})
        ENDFOREACH(MOCFile)
    ENDIF(${PROJECT_NAME} STREQUAL "OSGWindowQT4")

    ############
    # Flex/Bison
    ############

    IF(OSG_ENABLE_SCANPARSE_REGEN AND FLEX_EXE AND BISON_EXE)

        FOREACH(YYFile ${${PROJECT_NAME}_YY})

            GET_FILENAME_COMPONENT(YYBase ${YYFile} NAME_WE)

            STRING(REPLACE "Parser" "_" YYOpt ${YYBase})

            SET(YYSrc ${CMAKE_CURRENT_BINARY_DIR}/${YYBase}.cpp)
            SET(YYHdr ${CMAKE_CURRENT_BINARY_DIR}/${YYBase}.hpp)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${YYSrc} ${YYHdr}
                COMMAND ${BISON_EXE} -d -v -p${YYOpt} -b${YYOpt} -o ${YYSrc} ${YYFile}
                MAIN_DEPENDENCY ${YYFile})

            LIST(APPEND ${PROJECT_NAME}_SRC ${YYSrc})
            LIST(APPEND ${PROJECT_NAME}_HDR ${YYHdr})

        ENDFOREACH()

        FOREACH(LLFile ${${PROJECT_NAME}_LL})

            GET_FILENAME_COMPONENT(LLBase ${LLFile} NAME_WE)

            STRING(REPLACE "Scanner" "_" LLOpt ${LLBase})

            SET(LLSrc ${CMAKE_CURRENT_BINARY_DIR}/${LLBase}.cpp)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${LLSrc}
                COMMAND ${FLEX_EXE} -+ -P${LLOpt} -t ${LLFile} >  ${LLSrc}
                MAIN_DEPENDENCY ${LLFile})

            SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${LLSrc})

        ENDFOREACH()

        IF(${PROJECT_NAME}_YY OR ${PROJECT_NAME}_LL)
            SET(${PROJECT_NAME}_INC ${${PROJECT_NAME}_INC} ${CMAKE_CURRENT_BINARY_DIR})

            FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
                "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_CURRENT_BINARY_DIR}\")\n\n")

        ENDIF(${PROJECT_NAME}_YY OR ${PROJECT_NAME}_LL)

    ENDIF(OSG_ENABLE_SCANPARSE_REGEN AND FLEX_EXE AND BISON_EXE)

    ###############
    # build the lib
    ###############

    ## LINK_DIRS have to go first, before the ADD_LIB statement

    FOREACH(LIBDIR ${OSG_GLOBAL_DEP_LIBDIR})
        OSG_MSG("  (global) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_MSG("  (global) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)


    #Add Source Files to Source Groups
    #Loop through all of the groups for this Project
    FOREACH(PROJECT_SOURCE_GROUP_NAME ${${PROJECT_NAME}_SOURCE_GROUPS})
        STRING(REPLACE "\\" "_" THE_SOURCE_GROUP ${PROJECT_SOURCE_GROUP_NAME})
        SOURCE_GROUP(${PROJECT_SOURCE_GROUP_NAME} FILES
                     ${${PROJECT_NAME}_SOURCE_GROUP_${THE_SOURCE_GROUP}})
    ENDFOREACH(PROJECT_SOURCE_GROUP_NAME)

    ADD_LIBRARY(${PROJECT_NAME} ${${PROJECT_NAME}_SRC}
                                ${${PROJECT_NAME}_HDR}
                                ${${PROJECT_NAME}_INL}
                                ${${PROJECT_NAME}_INS})

    ADD_DEPENDENCIES(OSGAllLibs ${PROJECT_NAME})
    ADD_DEPENDENCIES(${OSG_MAIN_LIB_TARGET} ${PROJECT_NAME})

    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})

    SET(_OSG_DEBUG_POSTFIX "")

    IF(WIN32)
        SET(_OSG_DEBUG_POSTFIX DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
        DEFINE_SYMBOL ${PROJ_DEFINE}
        VERSION ${OSG_VERSION}
        SOVERSION ${OSG_VERSION}
        ${_OSG_DEBUG_POSTFIX}
        DEBUGOPT_POSTFIX "DO"
        RELEASENOOPT_POSTFIX "RN")

    IF(${PROJECT_NAME}_SUFFIX)
      SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
                            SUFFIX ${${PROJECT_NAME}_SUFFIX})

    ENDIF(${PROJECT_NAME}_SUFFIX)

    # dependencies - OpenSG
    OSG_GET_ALL_DEP_OSG_LIB(
        "${${PROJECT_NAME}_DEP_OSG_LIB}" DEP_OSG_LIST DEP_MISSING_LIST)

    # a lib with missing dependencies is fatal - it should not have made it here
    IF(DEP_MISSING_LIST)
        MESSAGE(FATAL_ERROR "Project ${PROJECT_NAME} has missing dependencies: ${DEP_MISSING_LIST}")
    ENDIF(DEP_MISSING_LIST)

    FOREACH(OSGDEP ${DEP_OSG_LIST})
        OSG_CHECKED_INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})
    ENDFOREACH(OSGDEP)

    FOREACH(OSGDEP ${${PROJECT_NAME}_DEP_OSG_LIB})
        OSG_CHECKED_INCLUDE  ("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")

        SET(${_OSGDEP_IMPORTED} FALSE)

        IF(TARGET ${OSGDEP})
          GET_PROPERTY(_OSGDEP_IMPORTED TARGET ${OSGDEP} PROPERTY IMPORTED)
        ENDIF(TARGET ${OSGDEP})

        IF(NOT _OSGDEP_IMPORTED)
          ADD_DEPENDENCIES     (${PROJECT_NAME} ${OSGDEP})
        ENDIF(NOT _OSGDEP_IMPORTED)

        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OSGDEP})
    ENDFOREACH(OSGDEP)

    # dependencies - global
    FOREACH(INCDIR ${OSG_GLOBAL_DEP_INCDIR})
        OSG_MSG("  (global) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIB ${OSG_GLOBAL_DEP_LIBS})
        OSG_MSG("  (global) - library ${LIB} = ${${LIB}}")
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${${LIB}})
    ENDFOREACH(LIB)

    IF(OSG_GLOBAL_DEP_DEFS)
        OSG_MSG("  (global) - definitions = ${OSG_GLOBAL_DEP_DEFS}")
        SET_PROPERTY(TARGET ${PROJECT_NAME}
            APPEND PROPERTY COMPILE_DEFINITIONS ${OSG_GLOBAL_DEP_DEFS})
    ENDIF(OSG_GLOBAL_DEP_DEFS)

    # dependencies - External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_MSG("  (external) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIB ${${PROJECT_NAME}_DEP_LIB})
        OSG_MSG("  (external) - library ${LIB} = ${${LIB}}")
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${${LIB}})
    ENDFOREACH(LIB)

    IF(${PROJECT_NAME}_DEP_DEFS)
        OSG_MSG("  (external) - definitions = ${${PROJECT_NAME}_DEP_DEFS}")
        SET_PROPERTY(TARGET ${PROJECT_NAME}
            APPEND PROPERTY COMPILE_DEFINITIONS ${${PROJECT_NAME}_DEP_DEFS})
    ENDIF(${PROJECT_NAME}_DEP_DEFS)

    IF(${PROJECT_NAME}_CXXFLAGS)
      SET_PROPERTY(TARGET ${PROJECT_NAME}
                    APPEND PROPERTY COMPILE_FLAGS ${${PROJECT_NAME}_CXXFLAGS})
    ENDIF(${PROJECT_NAME}_CXXFLAGS)

    IF(OSG_IGNORE_INSTALL_${PROJECT_NAME})
      RETURN()
    ENDIF()

    # install rules
    IF(WIN32)

        IF(OSG_INSTALL_SUBDIR)
            SET(_OSG_ISC "${OSG_INSTALL_SUBDIR}/")
        ELSE(OSG_INSTALL_SUBDIR)
            SET(_OSG_ISC "")
        ENDIF(OSG_INSTALL_SUBDIR)

        IF(OSG_USE_SEPARATE_LIBDIRS)
          SET(_OSG_TARGET_BINDIR_REL bin/${_OSG_ISC}rel)
          SET(_OSG_TARGET_BINDIR_DBG bin/${_OSG_ISC}debug)
          SET(_OSG_TARGET_BINDIR_RELNO bin/${_OSG_ISC}relnoopt)
          SET(_OSG_TARGET_BINDIR_DBGO bin/${_OSG_ISC}debugopt)

          SET(_OSG_TARGET_LIBDIR_REL lib/${_OSG_ISC}rel)
          SET(_OSG_TARGET_LIBDIR_DBG lib/${_OSG_ISC}debug)
          SET(_OSG_TARGET_LIBDIR_RELNO lib/${_OSG_ISC}relnoopt)
          SET(_OSG_TARGET_LIBDIR_DBGO lib/${_OSG_ISC}debugopt)
        ELSE(OSG_USE_SEPARATE_LIBDIRS)
          SET(_OSG_TARGET_BINDIR_REL bin/${_OSG_ISC})
          SET(_OSG_TARGET_BINDIR_DBG bin/${_OSG_ISC})
          SET(_OSG_TARGET_BINDIR_RELNO bin/${_OSG_ISC})
          SET(_OSG_TARGET_BINDIR_DBGO bin/${_OSG_ISC})

          SET(_OSG_TARGET_LIBDIR_REL lib/${_OSG_ISC})
          SET(_OSG_TARGET_LIBDIR_DBG lib/${_OSG_ISC})
          SET(_OSG_TARGET_LIBDIR_RELNO lib/${_OSG_ISC})
          SET(_OSG_TARGET_LIBDIR_DBGO lib/${_OSG_ISC})
        ENDIF(OSG_USE_SEPARATE_LIBDIRS)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Release
                RUNTIME DESTINATION ${_OSG_TARGET_BINDIR_REL}
                COMPONENT release_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Release
                LIBRARY DESTINATION ${_OSG_TARGET_LIBDIR_REL}
                ARCHIVE DESTINATION ${_OSG_TARGET_LIBDIR_REL}
                COMPONENT release_libraries)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Debug
                RUNTIME DESTINATION ${_OSG_TARGET_BINDIR_DBG}
                COMPONENT debug_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Debug
                LIBRARY DESTINATION ${_OSG_TARGET_LIBDIR_DBG}
                ARCHIVE DESTINATION ${_OSG_TARGET_LIBDIR_DBG}
                COMPONENT debug_libraries)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS ReleaseNoOpt
                RUNTIME DESTINATION ${_OSG_TARGET_BINDIR_RELNO}
                COMPONENT release_no_opt_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS ReleaseNoOpt
                LIBRARY DESTINATION ${_OSG_TARGET_LIBDIR_RELNO}
                ARCHIVE DESTINATION ${_OSG_TARGET_LIBDIR_RELNO}
                COMPONENT release_no_opt_libraries)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS DebugOpt
                RUNTIME DESTINATION ${_OSG_TARGET_BINDIR_DBGO}
                COMPONENT debug_opt_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS DebugOpt
                LIBRARY DESTINATION ${_OSG_TARGET_LIBDIR_DBGO}
                ARCHIVE DESTINATION ${_OSG_TARGET_LIBDIR_DBGO}
                COMPONENT debug_opt_libraries)


        IF(OSG_INSTALL_PDB_FILES)

          GET_TARGET_PROPERTY(_TMPVAL ${PROJECT_NAME} Release_LOCATION)

          STRING(REPLACE "dll" "pdb" _TMPVAL1 ${_TMPVAL})

          INSTALL(FILES ${_TMPVAL1}
                  CONFIGURATIONS Release
                  DESTINATION ${_OSG_TARGET_BINDIR_REL}
                  COMPONENT release_program_db)


          GET_TARGET_PROPERTY(_TMPVAL ${PROJECT_NAME} Debug_LOCATION)

          STRING(REPLACE "dll" "pdb" _TMPVAL1 ${_TMPVAL})

          INSTALL(FILES ${_TMPVAL1}
                  CONFIGURATIONS Debug
                  DESTINATION ${_OSG_TARGET_BINDIR_DBG}
                  COMPONENT debug_program_db)


          GET_TARGET_PROPERTY(_TMPVAL ${PROJECT_NAME} ReleaseNoOpt_LOCATION)

          STRING(REPLACE "dll" "pdb" _TMPVAL1 ${_TMPVAL})

          INSTALL(FILES ${_TMPVAL1}
                  CONFIGURATIONS ReleaseNoOpt
                  DESTINATION ${_OSG_TARGET_BINDIR_RELNO}
                  COMPONENT release_no_opt_program_db)


          GET_TARGET_PROPERTY(_TMPVAL ${PROJECT_NAME} DebugOpt_LOCATION)

          STRING(REPLACE "dll" "pdb" _TMPVAL1 ${_TMPVAL})

          INSTALL(FILES ${_TMPVAL1}
                  CONFIGURATIONS DebugOpt
                  DESTINATION ${_OSG_TARGET_BINDIR_DBGO}
                  COMPONENT debug_opt_program_db)

        ENDIF(OSG_INSTALL_PDB_FILES)


        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS MinSizeRel
                RUNTIME DESTINATION lib/minsizerel
                COMPONENT release_minsize_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS MinSizeRel
                LIBRARY DESTINATION lib/minsizerel
                ARCHIVE DESTINATION lib/minsizerel
                COMPONENT release_minsize_libraries)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS RelWithDebInfo
                RUNTIME DESTINATION lib/relwithdbg
                COMPONENT release_with_debinfo_runtimes)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS RelWithDebInfo
                RUNTIME DESTINATION lib/relwithdbg
                COMPONENT release_with_debinfo_libraries)
    ELSE(WIN32)
        INSTALL(TARGETS ${PROJECT_NAME}
                RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX}
                COMPONENT libraries)
    ENDIF(WIN32)

    INSTALL(FILES ${${PROJECT_NAME}_HDR}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ
                COMPONENT code_headers)

    INSTALL(FILES ${${PROJECT_NAME}_INL}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ
                COMPONENT code_headers)

    INSTALL(FILES ${${PROJECT_NAME}_INS}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ
                COMPONENT code_headers)

ENDFUNCTION(OSG_SETUP_LIBRARY_BUILD)


#############################################################################
# perform default actions for pass OSGSETUPTEST

FUNCTION(OSG_SETUP_TEST_BUILD)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPTEST")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPTEST")

    OSG_CHECKED_INCLUDE(${${PROJECT_NAME}_BUILD_FILE})
    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})

    # dependencies - OpenSG
    OSG_GET_ALL_DEP_OSG_LIB(
        "${${PROJECT_NAME}_DEP_OSG_LIB}" DEP_OSG_LIB DEP_MISSING_LIST)

    # if depencies are missing we skip the tests
    IF(DEP_MISSING_LIST)
        MESSAGE(STATUS "Tests for project ${PROJECT_NAME} have missing dependencies: ${DEP_MISSING_LIST} - skipping")
        RETURN()
    ENDIF(DEP_MISSING_LIST)

    FOREACH(OSGDEP ${DEP_OSG_LIB})
        OSG_CHECKED_INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})
    ENDFOREACH(OSGDEP)

    # dependencies - test OpenSG
    OSG_GET_ALL_DEP_OSG_LIB(
        "${${PROJECT_NAME}_DEP_TEST_OSG_LIB}" DEP_TEST_OSG_LIB DEP_MISSING_LIST)

    # if depencies are missing we skip the tests
    IF(DEP_MISSING_LIST)
        MESSAGE(STATUS "Tests for project ${PROJECT_NAME} have missing dependencies: ${DEP_MISSING_LIST} - skipping")
        RETURN()
    ENDIF(DEP_MISSING_LIST)

    FOREACH(OSGTESTDEP ${DEP_TEST_OSG_LIB})
        OSG_CHECKED_INCLUDE("${CMAKE_BINARY_DIR}/${OSGTESTDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGTESTDEP}_INC})
    ENDFOREACH(OSGTESTDEP)

    # dependencies - global
    FOREACH(INCDIR ${OSG_GLOBAL_DEP_INCDIR})
        OSG_MSG("  (global) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${OSG_GLOBAL_DEP_LIBDIR})
        OSG_MSG("  (global) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    # dependencies - External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_MSG("  (external) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_MSG("  (external) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    # dependencies - test External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR})
        OSG_MSG("  (test) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_TEST_LIBDIR})
        OSG_MSG("  (test) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    # build test programs
    FOREACH(EXE_SRC ${${PROJECT_NAME}_TEST_SRC})
        GET_FILENAME_COMPONENT(EXE ${EXE_SRC} NAME_WE)

        ADD_EXECUTABLE(${EXE} ${OSGEXCLUDE_TESTS} ${EXE_SRC} )

        ADD_DEPENDENCIES(OSGAllTests ${EXE})

        FOREACH(OSGTESTDEP ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})
            GET_PROPERTY(_OSGTESTDEP_IMPORTED TARGET ${OSGTESTDEP} PROPERTY IMPORTED)

            IF(NOT _OSGTESTDEP_IMPORTED)
              ADD_DEPENDENCIES(${EXE} ${OSGTESTDEP})
            ENDIF(NOT _OSGTESTDEP_IMPORTED)

            TARGET_LINK_LIBRARIES(${EXE} ${OSGTESTDEP})
        ENDFOREACH(OSGTESTDEP)

        FOREACH(OSGTESTDEP ${${PROJECT_NAME}_DEP_TEST_OSG_EEX_LIB})
            IF(TARGET ${OSGTESTDEP})
              GET_PROPERTY(_OSGTESTDEP_IMPORTED TARGET ${OSGTESTDEP} PROPERTY IMPORTED)

              IF(NOT _OSGTESTDEP_IMPORTED)
                ADD_DEPENDENCIES(${EXE} ${OSGTESTDEP})
              ENDIF(NOT _OSGTESTDEP_IMPORTED)

              TARGET_LINK_LIBRARIES(${EXE} ${OSGTESTDEP})
            ENDIF(TARGET ${OSGTESTDEP})
        ENDFOREACH(OSGTESTDEP)

        FOREACH(LIB ${${PROJECT_NAME}_DEP_TEST_LIB})
            OSG_MSG("  (test) - library ${LIB} = ${${LIB}}")
            TARGET_LINK_LIBRARIES(${EXE} ${${LIB}})
        ENDFOREACH(LIB)

        IF(NOT ${PROJECT_NAME}_NO_LIB)
          TARGET_LINK_LIBRARIES(${EXE} ${PROJECT_NAME})
        ENDIF(NOT ${PROJECT_NAME}_NO_LIB)

        IF(${PROJECT_NAME}_DEP_DEFS)
            OSG_MSG("  (external) - definitions ${PROJECT_NAME}_DEP_DEFS = ${${PROJECT_NAME}_DEP_DEFS}")
            SET_PROPERTY(TARGET ${EXE} APPEND
                PROPERTY COMPILE_DEFINITIONS ${${PROJECT_NAME}_DEP_DEFS})
        ENDIF(${PROJECT_NAME}_DEP_DEFS)

        IF(${PROJECT_NAME}_CXXFLAGS)
          SET_PROPERTY(TARGET ${EXE}
                       APPEND PROPERTY COMPILE_FLAGS ${${PROJECT_NAME}_CXXFLAGS})
        ENDIF(${PROJECT_NAME}_CXXFLAGS)

        IF(${PROJECT_NAME}_DEP_TEST_DEFS)
            OSG_MSG("  (test) - definitions ${PROJECT_NAME}_DEP_TEST_DEFS = ${${PROJECT_NAME}_DEP_TEST_DEFS}")
            SET_PROPERTY(TARGET ${EXE} APPEND
                PROPERTY COMPILE_DEFINITIONS ${${PROJECT_NAME}_DEP_TEST_DEFS})
        ENDIF(${PROJECT_NAME}_DEP_TEST_DEFS)
    ENDFOREACH(EXE_SRC)

ENDFUNCTION(OSG_SETUP_TEST_BUILD)


#############################################################################
# perform default actions for pass OSGSETUPUNITTEST

FUNCTION(OSG_SETUP_UNITTEST_BUILD)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPUNITTEST")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPUNITTEST")

    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

    # are there unittests to build?
    IF(NOT ${PROJECT_NAME}_UNITTEST_SRC)
        RETURN()
    ENDIF(NOT ${PROJECT_NAME}_UNITTEST_SRC)

    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})
    INCLUDE_DIRECTORIES(${OSG_UNITTEST_INCLUDE_DIRS})

    # dependencies - OpenSG
    OSG_GET_ALL_DEP_OSG_LIB(
        "${${PROJECT_NAME}_DEP_OSG_LIB}" DEP_OSG_LIB DEP_MISSING_LIST)

    # if depencies are missing we skip the unittests
    IF(DEP_MISSING_LIST)
        MESSAGE(STATUS "Unittests for project ${PROJECT_NAME} have missing dependencies: ${DEP_MISSING_LIST} - skipping")
        RETURN()
    ENDIF(DEP_MISSING_LIST)

    FOREACH(OSGDEP ${DEP_OSG_LIB})
        OSG_CHECKED_INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})
    ENDFOREACH(OSGDEP)

    # dependencies - unittest OpenSG
    OSG_GET_ALL_DEP_OSG_LIB(
        "${${PROJECT_NAME}_DEP_UNITTEST_OSG_LIB}" DEP_UNITTEST_OSG_LIB DEP_MISSING_LIST)

    # if depencies are missing we skip the unittests
    IF(DEP_MISSING_LIST)
        MESSAGE(STATUS "Unittests for project ${PROJECT_NAME} have missing dependencies: ${DEP_MISSING_LIST} - skipping")
        RETURN()
    ENDIF(DEP_MISSING_LIST)

    FOREACH(OSGDEP ${DEP_UNITTEST_OSG_LIB})
        OSG_CHECKED_INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})
    ENDFOREACH(OSGDEP)

    # dependencies global
    FOREACH(INCDIR ${OSG_GLOBAL_DEP_INCDIR})
        OSG_MSG("  (global) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${OSG_GLOBAL_DEP_LIBDIR})
        OSG_MSG("  (global) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    # dependencies - unittest External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_UNITTEST_INCDIR})
        OSG_MSG("  (unittest) - include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_UNITTEST_LIBDIR})
        OSG_MSG("  (unittest) - library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    LINK_DIRECTORIES(${OSG_UNITTEST_LIBRARY_DIRS})

    # add the unittest runner source
    LIST(APPEND ${PROJECT_NAME}_UNITTEST_SRC
        "${CMAKE_SOURCE_DIR}/Tools/unittest-cpp/UnitTestRunner.cpp")

    # build unittest executable
    ADD_EXECUTABLE("UnitTest${PROJECT_NAME}"
                   ${OSGEXCLUDE_UNITTESTS}
                   ${${PROJECT_NAME}_UNITTEST_SRC})

    ADD_DEPENDENCIES(OSGAllUnitTests UnitTest${PROJECT_NAME})

    TARGET_LINK_LIBRARIES("UnitTest${PROJECT_NAME}" "${OSG_UNITTEST_LIBRARY}")
    TARGET_LINK_LIBRARIES("UnitTest${PROJECT_NAME}" ${PROJECT_NAME})

    FOREACH(OSGDEP ${${PROJECT_NAME}_DEP_UNITTEST_OSG_LIB})
        ADD_DEPENDENCIES("UnitTest${PROJECT_NAME}" ${OSGDEP})
        TARGET_LINK_LIBRARIES("UnitTest${PROJECT_NAME}" ${OSGDEP})
    ENDFOREACH(OSGDEP)

    FOREACH(LIB ${${PROJECT_NAME}_DEP_UNITTEST_LIB})
        OSG_MSG("  (unittest) - library ${LIB} = ${${LIB}}")
        TARGET_LINK_LIBRARIES("UnitTest${PROJECT_NAME}" ${${LIB}})
    ENDFOREACH(LIB)

    #MESSAGE("--------- ADDING TEST --------- ${PROJECT_NAME}") # Trips up ccmake
    ADD_TEST("UnitTest${PROJECT_NAME}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UnitTest${PROJECT_NAME}")

ENDFUNCTION(OSG_SETUP_UNITTEST_BUILD)

#############################################################################
# perform default actions for pass OSGDOXYDOC

FUNCTION(OSG_SETUP_SEPARATE_LIBS_DOXYDOC)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")
        RETURN()
    ENDIF()

    IF(${PROJECT_NAME}_NO_DOC)
        RETURN()
    ENDIF(${PROJECT_NAME}_NO_DOC)

    # set up variables for the config file
    SET(OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE_IN "${CMAKE_SOURCE_DIR}/Doc/opensg-doxy.in")
    SET(OSG_${PROJECT_NAME}_DOC_DIRECTORY              "${OSG_DOXY_HTML_DIR}/${PROJECT_NAME}")
    SET(OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE    "${CMAKE_BINARY_DIR}/Doc/${PROJECT_NAME}-doxy")

    SET(OSG_${PROJECT_NAME}_DEP_DOXY_TAGFILES"")
    SET(OSG_${PROJECT_NAME}_DOXY_TAGFILE     "${CMAKE_BINARY_DIR}/Doc/${PROJECT_NAME}_DOXYGEN_TAGS")
    SET(OSG_${PROJECT_NAME}_DEP_DOCS         "")

    # dependencies - OpenSG
    OSG_GET_ALL_DEP_OSG_LIB("${${PROJECT_NAME}_DEP_OSG_LIB}" DEP_OSG_LIST DEP_MISSING_LIST)

    FOREACH(OSGDEP ${DEP_OSG_LIST})
        SET(OSG_${PROJECT_NAME}_DEP_DOXY_TAGFILES "${OSG_${PROJECT_NAME}_DEP_DOXY_TAGFILES} ./${OSGDEP}_DOXYGEN_TAGS=../../${OSGDEP}/html")
        LIST(APPEND OSG_${PROJECT_NAME}_DEP_DOCS "${OSGDEP}Doc")
    ENDFOREACH()

    IF(OSG_${PROJECT_NAME}_DOXY_EXTERNAL_INCLUDE)

      GET_FILENAME_COMPONENT(_OSG_DOC_INCLUDE ${OSG_${PROJECT_NAME}_DOXY_EXTERNAL_INCLUDE} NAME)

      CONFIGURE_FILE("${OSG_${PROJECT_NAME}_DOXY_EXTERNAL_INCLUDE}"
                     "${CMAKE_BINARY_DIR}/Doc/Include/${_OSG_DOC_INCLUDE}")

    ENDIF()

    IF(EXISTS "${CMAKE_BINARY_DIR}/Doc/Include/${PROJECT_NAME}.include")
      SET(OSG_DOC_BASIC_INPUT "${CMAKE_BINARY_DIR}/Doc/Include/${PROJECT_NAME}.include")
    ENDIF()

    # write doxygen config file
    CONFIGURE_FILE("${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE_IN}"
                   "${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE}")

    SET(OSG_DOC_BASIC_INPUT "${CMAKE_BINARY_DIR}/Doc/Include/OSGDummy.include")

    IF(DOXYGEN_EXECUTABLE)
        #ADD_CUSTOM_TARGET(DocUpload COMMAND unison -batch -ui text opensg_doc)
        #ADD_DEPENDENCIES(DocUpload Doc)

        SET(OSG_DOC_PIPES "")

        IF(OSG_DOXY_STDOUT_LOG)
          SET(OSG_DOC_PIPES > ${OSG_DOXY_STDOUT_LOG}.${PROJECT_NAME})
        ENDIF(OSG_DOXY_STDOUT_LOG)

        ADD_CUSTOM_TARGET(${PROJECT_NAME}DocOnly
            VERBATIM
            COMMAND ${DOXYGEN_EXECUTABLE} ${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE} ${OSG_DOC_PIPES}
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Doc")

        ADD_CUSTOM_TARGET(${PROJECT_NAME}Doc
            VERBATIM
            COMMAND ${DOXYGEN_EXECUTABLE} ${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE} ${OSG_DOC_PIPES}
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Doc")

        FOREACH(OSGDEPDOC ${OSG_${PROJECT_NAME}_DEP_DOCS})
            ADD_DEPENDENCIES(${PROJECT_NAME}Doc ${OSGDEPDOC})
        ENDFOREACH()

        ADD_DEPENDENCIES(Doc ${PROJECT_NAME}Doc)
    ENDIF()

    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

    FILE(APPEND ${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE}
        "# source code input files for ${PROJECT_NAME}\n\n")

    FOREACH(INCDIR ${${PROJECT_NAME}_INC})
        FILE(APPEND ${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE}
            "INPUT += ${INCDIR}\n")
    ENDFOREACH()

    FILE(APPEND ${OSG_${PROJECT_NAME}_DOXY_CONFIGURATION_FILE} "\n")

    #Tree Code
    STRING(REGEX MATCH OSGContrib*|OSGTest* _OSG_IS_CONTRIBLIB ${PROJECT_NAME})

    STRING(REPLACE "OSG" "" LIBTREENAME "${PROJECT_NAME}")
    STRING(REPLACE "Contrib" "" LIBTREENAME "${LIBTREENAME}")

    IF(_OSG_IS_CONTRIBLIB)
        FILE(APPEND "${OSG_DOXY_DOC_TREE_SCRIPT}"
            "      insDoc(ContribNode, gLnk(\"R\", \"${LIBTREENAME}\", \"${OSG_DOXY_BASELIB_DOC_HTML_INDEX}/${PROJECT_NAME}/html/index.html\"))
")
    ELSE()
        FILE(APPEND "${OSG_DOXY_DOC_TREE_SCRIPT}"
            "      insDoc(CoreNode, gLnk(\"R\", \"${LIBTREENAME}\", \"${OSG_DOXY_BASELIB_DOC_HTML_INDEX}/${PROJECT_NAME}/html/index.html\"))
")
    ENDIF()

ENDFUNCTION(OSG_SETUP_SEPARATE_LIBS_DOXYDOC)

#############################################################################
# perform default actions for pass OSGDOXYDOC

FUNCTION(OSG_SETUP_DOXYDOC)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")

    IF(${PROJECT_NAME}_NO_DOC)
        RETURN()
    ENDIF(${PROJECT_NAME}_NO_DOC)


    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
        "#############################################################################\n"
        )
    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
        "# doc input files for ${PROJECT_NAME}\n\n"
        )

    FOREACH(INCDIR ${${PROJECT_NAME}_INC})
        FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
            "INPUT += ${INCDIR}\n")
    ENDFOREACH(INCDIR)

    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE} "\n")

ENDFUNCTION(OSG_SETUP_DOXYDOC)

#############################################################################
# perform default actions for build passes

FUNCTION(OSG_SETUP_PROJECT PROJ_DEFINE)

    FOREACH(_OSG_${PROJECT_NAME}_EXT_DIR ${${PROJECT_NAME}_EXT_DIRS})
      OSG_ADD_DIRECTORY(${_OSG_${PROJECT_NAME}_EXT_DIR})
    ENDFOREACH(_OSG_${PROJECT_NAME}_EXT_DIR ${${PROJECT_NAME}_EXT_DIRS})

    IF(OSG_CMAKE_PASS STREQUAL "OSGSETUP")
        OSG_SETUP_LIBRARY_BUILD(${PROJ_DEFINE})

    ELSEIF(OSG_CMAKE_PASS STREQUAL "OSGSETUPTEST")
        OSG_SETUP_TEST_BUILD()

    ELSEIF(OSG_CMAKE_PASS STREQUAL "OSGSETUPUNITTEST")
        OSG_SETUP_UNITTEST_BUILD()

    ELSEIF(OSG_CMAKE_PASS STREQUAL "OSGDOXYDOC")
        IF(OSG_GENERATE_SEPARATE_LIB_DOC)
            OSG_SETUP_SEPARATE_LIBS_DOXYDOC()
        ELSE()
            OSG_SETUP_DOXYDOC()
        ENDIF()

    ENDIF(OSG_CMAKE_PASS STREQUAL "OSGSETUP")

ENDFUNCTION(OSG_SETUP_PROJECT)

#############################################################################
# setup import targets so the debug/debugopt build type works correctly

FUNCTION(OSG_SETUP_IMPORT_LIB_WINDOWS NEW_LIB)

  IF(${NEW_LIB}_RELEASE)
      GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR ${${NEW_LIB}_RELEASE} PATH)
  ENDIF(${NEW_LIB}_RELEASE)

  IF(NOT OSG_TMP_LIB_DIR AND ${NEW_LIB}_DEBUG)
      GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR ${${NEW_LIB}_DEBUG} PATH)
  ENDIF(NOT OSG_TMP_LIB_DIR AND ${NEW_LIB}_DEBUG)


  SET_TARGET_PROPERTIES(OSG_${NEW_LIB}_TARGET PROPERTIES
                        IMPORTED_IMPLIB_RELEASE ${${NEW_LIB}_RELEASE}
                        IMPORTED_LOCATION_RELEASE ${OSG_TMP_LIB_DIR}
                        IMPORTED_IMPLIB_RELEASENOOPT ${${NEW_LIB}_RELEASE}
                        IMPORTED_LOCATION_RELEASENOOPT ${OSG_TMP_LIB_DIR}
                        IMPORTED_IMPLIB_DEBUG ${${NEW_LIB}_DEBUG}
                        IMPORTED_LOCATION_DEBUG ${OSG_TMP_LIB_DIR}
                        IMPORTED_IMPLIB_DEBUGOPT ${${NEW_LIB}_DEBUG}
                        IMPORTED_LOCATION_DEBUGOPT ${OSG_TMP_LIB_DIR})

ENDFUNCTION(OSG_SETUP_IMPORT_LIB_WINDOWS)

FUNCTION(OSG_SETUP_IMPORT_LIB_UNIX NEW_LIB)

  IF(${NEW_LIB}_RELEASE)
      GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR ${${NEW_LIB}_RELEASE} PATH)
  ENDIF(${NEW_LIB}_RELEASE)

  IF(NOT OSG_TMP_LIB_DIR AND ${NEW_LIB}_DEBUG)
      GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR ${${NEW_LIB}_DEBUG} PATH)
  ENDIF(NOT OSG_TMP_LIB_DIR AND ${NEW_LIB}_DEBUG)

  IF(${NEW_LIB}_RELEASE AND NOT ${NEW_LIB}_DEBUG)
    SET(${NEW_LIB}_DEBUG ${${NEW_LIB}_RELEASE} CACHE FILEPATH "" FORCE)
  ENDIF(${NEW_LIB}_RELEASE AND NOT ${NEW_LIB}_DEBUG)

  IF(NOT ${NEW_LIB}_RELEASE AND ${NEW_LIB}_DEBUG)
    SET(${NEW_LIB}_RELEASE ${${NEW_LIB}_DEBUG} CACHE FILEPATH "" FORCE)
  ENDIF(NOT ${NEW_LIB}_RELEASE AND ${NEW_LIB}_DEBUG)

  SET_TARGET_PROPERTIES(OSG_${NEW_LIB}_TARGET PROPERTIES
                        IMPORTED_LOCATION ${${NEW_LIB}_RELEASE}
                        IMPORTED_LOCATION_DEBUG ${${NEW_LIB}_DEBUG}
                        IMPORTED_LOCATION_DEBUGGV ${${NEW_LIB}_DEBUG})

ENDFUNCTION(OSG_SETUP_IMPORT_LIB_UNIX)

MACRO(OSG_ADD_IMPORT_LIB LIB_LIST NEW_LIB)

    ADD_LIBRARY(OSG_${NEW_LIB}_TARGET SHARED IMPORTED)

    IF(WIN32)
      OSG_SETUP_IMPORT_LIB_WINDOWS(${NEW_LIB})
    ELSE(WIN32)
      OSG_SETUP_IMPORT_LIB_UNIX(${NEW_LIB})

      OSG_ADD_OPT(${NEW_LIB}_RELEASE)
      OSG_ADD_OPT(${NEW_LIB}_DEBUG)
      OSG_ADD_OPT(OSG_${NEW_LIB}_TARGET)
    ENDIF(WIN32)

    LIST(APPEND ${LIB_LIST} OSG_${NEW_LIB}_TARGET)

ENDMACRO(OSG_ADD_IMPORT_LIB)

##########################################################################
# write settings so different variants can be build with the same settings

MACRO(OSG_OPTION NAME DESC VALUE)
    LIST(APPEND OSG_OPTION_LIST ${NAME})
    OSG_MSG("adding option ${NAME} = ${VALUE}")

    OPTION(${NAME} "${DESC}" ${VALUE})
ENDMACRO(OSG_OPTION)

MACRO(OSG_SET_CACHE NAME VALUE TYPE DESC)
    LIST(APPEND OSG_OPTION_LIST ${NAME})

    SET(${NAME} ${VALUE} CACHE ${TYPE} "${DESC}")
ENDMACRO(OSG_SET_CACHE)

MACRO(OSG_SET NAME VALUE)
    LIST(APPEND OSG_OPTION_LIST ${NAME})

    SET(${NAME} ${VALUE})
ENDMACRO(OSG_SET)

MACRO(OSG_ADD_OPT NAME)
    LIST(APPEND OSG_OPTION_LIST ${NAME})
ENDMACRO(OSG_ADD_OPT)

MACRO(OSG_FIND_PACKAGE NAME)
    FIND_PACKAGE(${NAME})

    IF(${NAME}_FOUND)
        OSG_ADD_OPT(${NAME}_LIBRARIES)
        OSG_ADD_OPT(${NAME}_INCLUDE_DIR)
    ENDIF(${NAME}_FOUND)

    OSG_ADD_OPT(${NAME}_FOUND)
ENDMACRO(OSG_FIND_PACKAGE)

MACRO(OSG_BOOST_DEP_SETUP)
    SET(Boost_USE_MULTITHREAD ON )
    SET(Boost_USE_STATIC_LIBS OFF)

    FIND_PACKAGE(Boost COMPONENTS filesystem)

    IF(Boost_FOUND)

        IF(${Boost_MINOR_VERSION} GREATER 34)
          FIND_PACKAGE(Boost COMPONENTS system)
        ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        # Hide settings
        SET(Boost_FILESYSTEM_LIBRARY ${Boost_FILESYSTEM_LIBRARY}
                                     CACHE INTERNAL "")
        SET(Boost_FILESYSTEM_LIBRARY_DEBUG ${Boost_FILESYSTEM_LIBRARY_DEBUG}
                                           CACHE INTERNAL "")
        SET(Boost_FILESYSTEM_LIBRARY_RELEASE
           ${Boost_FILESYSTEM_LIBRARY_RELEASE}
           CACHE INTERNAL "")

        SET(Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR}
                              CACHE INTERNAL "")

        SET(Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS}
                               CACHE INTERNAL "")

        SET(Boost_USE_MULTITHREADED ${Boost_USE_MULTI_THREADED}
                                    CACHE INTERNAL "")


        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR} )

        IF(UNIX)
            LINK_DIRECTORIES   (${Boost_LIBRARY_DIRS})
        ENDIF(UNIX)

        IF(NOT Boost_USE_STATIC_LIBS)
          ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
        ENDIF(NOT Boost_USE_STATIC_LIBS)

        IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
           CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

          IF(${Boost_MINOR_VERSION} GREATER 34)
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG} 
                               ${Boost_SYSTEM_LIBRARY_DEBUG})
          ELSE()
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG})
          ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        ELSE()

          IF(${Boost_MINOR_VERSION} GREATER 34)
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE} 
                               ${Boost_SYSTEM_LIBRARY_RELEASE})
          ELSE()
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE})
          ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        ENDIF()

        SET(OSG_BOOST_INCDIRS ${Boost_INCLUDE_DIR})

    ENDIF(Boost_FOUND)
ENDMACRO(OSG_BOOST_DEP_SETUP)

FUNCTION(OSG_WRITE_SETTINGS FILENAME)
    FILE(WRITE ${FILENAME}
            "# CMake.settings -- auto generated\n\n")

    FOREACH(OSG_OPT ${OSG_OPTION_LIST})
      IF(TARGET ${OSG_OPT})
        STRING(REPLACE _TARGET "" _OSG_OPT_BASE ${OSG_OPT})
        STRING(REPLACE OSG_ "" _OSG_OPT_OSGBASE ${_OSG_OPT_BASE})

        IF(NOT ${_OSG_OPT_OSGBASE}_DEBUG)
          SET(${_OSG_OPT_OSGBASE}_DEBUG ${OSG_${_OSG_OPT_OSGBASE}_DEBUG})
        ENDIF()
        IF(NOT ${_OSG_OPT_OSGBASE}_RELEASE)
          SET(${_OSG_OPT_OSGBASE}_RELEASE ${OSG_${_OSG_OPT_OSGBASE}_RELEASE})
        ENDIF()

        FILE(APPEND ${FILENAME}
          "ADD_LIBRARY(${_OSG_OPT_BASE}_TARGET SHARED IMPORTED)\n"
          "SET_TARGET_PROPERTIES(${_OSG_OPT_BASE}_TARGET PROPERTIES\n"
          "                      IMPORTED_LOCATION ${${_OSG_OPT_OSGBASE}_RELEASE}\n"
          "                      IMPORTED_LOCATION_DEBUG ${${_OSG_OPT_OSGBASE}_DEBUG}\n"
          "                      IMPORTED_LOCATION_DEBUGGV ${${_OSG_OPT_OSGBASE}_DEBUG})\n")
      ELSE()
        FILE(APPEND ${FILENAME}
             "SET(${OSG_OPT} ${${OSG_OPT}} CACHE INTERNAL \"\")\n")
      ENDIF()
    ENDFOREACH(OSG_OPT ${OSG_OPTION_LIST})

ENDFUNCTION(OSG_WRITE_SETTINGS FILENAME)

FUNCTION(CHECK_BUILD_DIR)
  IF("${${CMAKE_PROJECT_NAME}_SOURCE_DIR}"  STREQUAL "${${CMAKE_PROJECT_NAME}_BINARY_DIR}")
    MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source Build. \n"
                        "Please create a separate binary directory and run "
                        "CMake there.")
  ENDIF("${${CMAKE_PROJECT_NAME}_SOURCE_DIR}"  STREQUAL "${${CMAKE_PROJECT_NAME}_BINARY_DIR}")
ENDFUNCTION(CHECK_BUILD_DIR)

MACRO(OSG_CHECK_INSTALL)

MESSAGE(STATUS  "process ignore install ${OSG_IGNORE_INSTALL}")

  IF(OSG_IGNORE_INSTALL)
    FOREACH(OSG_IGNORE_PRJ ${OSG_IGNORE_INSTALL})
      SET(OSG_IGNORE_INSTALL_${OSG_IGNORE_PRJ} TRUE)
    ENDFOREACH()
  ENDIF(OSG_IGNORE_INSTALL)
ENDMACRO(OSG_CHECK_INSTALL)

##########################################################################
# Add Tutorial builds as tests
#
FUNCTION(OSG_ADD_TUTORIAL_TESTS TUTORIALS_NAME TUTORIAL_SOURCE_DIR)
    IF(NOT OSGBUILD_UNITTESTS)
        RETURN()
    ENDIF()

    FILE(GLOB TUTORIAL_SOURCES "${TUTORIAL_SOURCE_DIR}/[0-9][0-9]*.cpp")

    FOREACH(TUTORIAL ${TUTORIAL_SOURCES})
        #Get the path to the tutorial executable
        STRING(LENGTH ${TUTORIAL} SOURCE_PATH_LENGTH)
        MATH(EXPR SOURCE_PATH_LENGTH '${SOURCE_PATH_LENGTH}-4')
        STRING(SUBSTRING ${TUTORIAL} 0 ${SOURCE_PATH_LENGTH} TUTORIAL_EXE_PATH )
        SET(TUTORIAL_EXE_PATH "${TUTORIAL_EXE_PATH}${CMAKE_EXECUTABLE_SUFFIX}")

        #Extract a short name for the tutorial test
        STRING(REGEX MATCH "([0-9][0-9].*)[.]cpp" TUTORIAL_NAME ${TUTORIAL})
        SET(TUTORIAL_NAME ${CMAKE_MATCH_1})

        #Add a test to see if the tutorial exists
        ADD_TEST(NAME "${TUTORIALS_NAME}-${TUTORIAL_NAME}"
                 COMMAND test -e ${TUTORIAL_EXE_PATH})
    ENDFOREACH()
ENDFUNCTION()
