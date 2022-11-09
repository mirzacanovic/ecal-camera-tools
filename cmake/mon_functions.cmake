function(add_mon_plugin TARGET_NAME)
  
  add_library(${TARGET_NAME} SHARED ${ARGN})
  target_link_libraries(${TARGET_NAME} protobuf::libprotobuf eCAL::core eCAL::hdf5 eCAL::mon_plugin_lib eCAL::proto)
  target_include_directories(${TARGET_NAME} PRIVATE src)
  if(MSVC)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "/wd4125 /wd4100 /wd4251 /wd4275 /wd4456 /wd4505 /wd4099")
    set_target_properties(${TARGET_NAME}  PROPERTIES  OUTPUT_NAME ${TARGET_NAME}_mon_plugin)
  else(MSVC)
    set_target_properties(${TARGET_NAME}  PROPERTIES  
	                      OUTPUT_NAME ${TARGET_NAME}_mon_plugin)
  endif()
endfunction()

function(install_mon_plugin TARGET_NAME)
  	install(TARGETS ${TARGET_NAME}
    		RUNTIME DESTINATION  "${eCAL_install_bin_dir}/${ECAL_MON_PLUGIN_DIR}" COMPONENT app
    		LIBRARY DESTINATION  $<IF:$<BOOL:${WIN32}>,${eCAL_install_bin_dir}/${ECAL_MON_PLUGIN_DIR},local/${eCAL_install_lib_dir}/${ECAL_MON_PLUGIN_DIR}> COMPONENT app
		ARCHIVE DESTINATION  lib COMPONENT app
  		)
endfunction()