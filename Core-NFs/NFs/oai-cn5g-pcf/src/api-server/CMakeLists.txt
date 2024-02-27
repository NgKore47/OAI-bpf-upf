################################################################################
#Licensed to the OpenAirInterface(OAI) Software Alliance under one or more
#contributor license agreements.See the NOTICE file distributed with
#this work for additional information regarding copyright ownership.
#The OpenAirInterface Software Alliance licenses this file to You under
#the OAI Public License, Version 1.1(the "License"); you may not use this file
#except in compliance with the License.
#You may obtain a copy of the License at
#
#http: // www.openairinterface.org/?page_id=698
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
#For more information about the OpenAirInterface(OAI) Software Alliance:
#contact @openairinterface.org
################################################################################

set(PCF_API_SERVER_DIR "${SRC_TOP_DIR}/api-server")

include_directories(${PCF_API_SERVER_DIR}/api)
include_directories(${PCF_API_SERVER_DIR}/impl)
include_directories(${PCF_API_SERVER_DIR}/handler)
include_directories(${PCF_API_SERVER_DIR}/)
include_directories(${SRC_TOP_DIR}/pcf_app)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/utils)
include_directories(${SRC_TOP_DIR}/${MOUNTED_COMMON}/logger)
include_directories(${SRC_TOP_DIR}/${MOUNTED_COMMON}/config)
include(${SRC_TOP_DIR}/${MOUNTED_COMMON}/model/common_model/common_model.cmake)
include(${SRC_TOP_DIR}/${MOUNTED_COMMON}/model/pcf/pcf_model.cmake)
include(${SRC_TOP_DIR}/${MOUNTED_COMMON}/model/smf/smf_model.cmake)

file(GLOB PCF_API_SERVER_src_files
    ${PCF_API_SERVER_DIR}/pcf-api-server.cpp
    ${PCF_API_SERVER_DIR}/pcf-http2-server.cpp
    ${PCF_API_SERVER_DIR}/api_defs.cpp
    ${PCF_API_SERVER_DIR}/api/*.cpp
    ${PCF_API_SERVER_DIR}/impl/*.cpp
    ${PCF_API_SERVER_DIR}/handler/*.cpp
)
 
add_library(PCF_API STATIC
           ${PCF_API_SERVER_src_files})
