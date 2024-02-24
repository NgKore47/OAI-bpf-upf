/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file nssf_http2-server.h
 \brief
 \author  Rohan Kharade
 \company Openairinterface Software Allianse
 \date 2021
 \email: rohan.kharade@openairinterface.org
 */

#include "nssf_config.hpp"
#include "if.hpp"
#include <nlohmann/json.hpp>

#include "nssf_config_types.hpp"

using namespace std;
using namespace oai::config::nssf;
using namespace oai::config;
using namespace oai::nssf_server::model;
using namespace oai::model::common;

nssf_nsi_info_t nssf_config::nssf_nsi_info;
nssf_ta_info_t nssf_config::nssf_ta_info;
nssf_amf_info_t nssf_config::nssf_amf_info;
// nlohmann::json nssf_config::nssf_slice_config;

nssf_config::nssf_config(
    const string& config_path, bool log_stdout, bool log_rot_file)
    : config(config_path, NSSF_CONFIG_NAME, log_stdout, log_rot_file) {
  m_used_config_values = {
      LOG_LEVEL_CONFIG_NAME, REGISTER_NF_CONFIG_NAME, NF_LIST_CONFIG_NAME,
      NSSF_CONFIG_NAME, NF_CONFIG_HTTP_NAME};
  m_used_sbi_values = {NSSF_CONFIG_NAME, NRF_CONFIG_NAME};

  auto nssf = std::make_shared<nssf_config_type>(
      NSSF_CONFIG_NAME, "oai-nssf",
      sbi_interface("SBI", "oai-nssf", 80, "v1", "eth0"),
      "/openair-nssf/etc/nssf_slice_config.yaml");

  auto nrf = std::make_shared<nf>(
      NRF_CONFIG_NAME, "oai-nrf",
      sbi_interface("SBI", "oai-nrf", 80, "v1", ""));

  add_nf(NSSF_CONFIG_NAME, nssf);
  add_nf(NRF_CONFIG_NAME, nrf);
}

//------------------------------------------------------------------------------
bool nssf_config::parse_nsi_info(const YAML::Node& conf, nssf_nsi_info_t& cfg) {
  static std::mutex mutex;
  try {
    for (YAML::const_iterator it = conf.begin(); it != conf.end(); ++it) {
      nsi_info_t nsi_info;
      const YAML::Node& nsiInfo = *it;

      // nsiInformationList
      nsi_info.nsi_info.setNrfId(
          nsiInfo["nsiInformationList"]["nrfId"].as<string>());
      if (nsiInfo["nsiInformationList"]["nsiId"])
        nsi_info.nsi_info.setNsiId(
            nsiInfo["nsiInformationList"]["nsiId"].as<string>());
      if (nsiInfo["nsiInformationList"]["nrfNfMgtUri"])
        nsi_info.nsi_info.setNrfNfMgtUri(
            nsiInfo["nsiInformationList"]["nrfNfMgtUri"].as<string>());

      // snssai
      nsi_info.snssai.setSst(nsiInfo["snssai"]["sst"].as<int32_t>());
      if (nsiInfo["snssai"]["sd"])
        nsi_info.snssai.setSd(nsiInfo["snssai"]["sd"].as<string>());

      std::lock_guard<std::mutex> lock(mutex);
      cfg.nsi_info_list.push_back(nsi_info);
    }
    cfg.nsi_info_list.shrink_to_fit();
  } catch (std::exception& e) {
    Logger::nssf_app().error("Error parsing NsiInfo");
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool nssf_config::parse_ta_info(const YAML::Node& conf, nssf_ta_info_t& cfg) {
  static std::mutex mutex;
  try {
    for (YAML::const_iterator it = conf.begin(); it != conf.end(); ++it) {
      ta_info_t ta_info;
      PlmnId plmn_id;
      const YAML::Node& taInfo = *it;

      // Set Tai
      plmn_id.setMcc(taInfo["tai"]["plmnId"]["mcc"].as<string>());
      plmn_id.setMnc(taInfo["tai"]["plmnId"]["mnc"].as<string>());
      ta_info.tai.setPlmnId(plmn_id);
      ta_info.tai.setTac(taInfo["tai"]["tac"].as<string>());

      // Set Supported Snssai List
      cfg.ta_info_list.push_back(ta_info);
    }
    cfg.ta_info_list.shrink_to_fit();
  } catch (std::exception& e) {
    Logger::nssf_app().error("Error parsing TaInfo");
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool nssf_config::parse_nssai(
    const YAML::Node& conf, SupportedNssaiAvailabilityData& nssai_data) {
  try {
    Tai tai;
    PlmnId plmn_id;
    std::vector<ExtSnssai> snssai_list;
    std::vector<Tai> tai_list;

    // Parse TAI
    tai.setTac(conf["tai"]["tac"].as<string>());
    plmn_id.setMcc(conf["tai"]["plmnId"]["mcc"].as<string>());
    plmn_id.setMcc(conf["tai"]["plmnId"]["mcc"].as<string>());
    tai.setPlmnId(plmn_id);
    nssai_data.setTai(tai);

    // Parse Supported Snssai List
    const YAML::Node& slices = conf["supportedSnssaiList"];
    for (YAML::const_iterator it = slices.begin(); it != slices.end(); ++it) {
      const YAML::Node& snssai = *it;
      ExtSnssai e_snssai;
      e_snssai.setSst(snssai["sst"].as<int32_t>());
      if (snssai["sd"]) e_snssai.setSd(snssai["sd"].as<string>());
      snssai_list.push_back(e_snssai);
    }
    nssai_data.setSupportedSnssaiList(snssai_list);

  } catch (std::exception& e) {
    Logger::nssf_app().error("Error parsing amfList");
    return false;
  }
  return true;
}
//------------------------------------------------------------------------------
bool nssf_config::parse_amf_list(const YAML::Node& conf, amf_info_t& amf_info) {
  static std::mutex mutex;
  try {
    for (YAML::const_iterator ita = conf.begin(); ita != conf.end(); ++ita) {
      const YAML::Node& amf = *ita;
      std::vector<SupportedNssaiAvailabilityData> nssai_data_list;
      SupportedNssaiAvailabilityData nssai_data;
      // ToDo:- Parse as a list
      parse_nssai(amf["supportedNssaiAvailabilityData"], nssai_data);
      nssai_data_list.push_back(nssai_data);
      amf_info.amf_List.emplace_back(amf["nfId"].as<string>(), nssai_data_list);
    }
  } catch (std::exception& e) {
    Logger::nssf_app().error("Error parsing amfList");
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool nssf_config::parse_amf_info(const YAML::Node& conf, nssf_amf_info_t& cfg) {
  static std::mutex mutex;
  try {
    for (YAML::const_iterator it = conf.begin(); it != conf.end(); ++it) {
      amf_info_t amf_info;
      const YAML::Node& amfInfo = *it;

      // amInfoList
      amf_info.target_amf_set  = amfInfo["targetAmfSet"].as<string>();
      amf_info.nrf_amf_set     = amfInfo["nrfAmfSet"].as<string>();
      amf_info.nrf_amf_set_mgt = amfInfo["nrfAmfSetNfMgtUri"].as<string>();
      if (!parse_amf_list(amfInfo["amfList"], amf_info)) throw std::exception();
      cfg.amf_info_list.push_back(amf_info);
    }
  } catch (std::exception& e) {
    Logger::nssf_app().error("Error parsing amfInfo");
    return false;
  }
  return true;
}
//------------------------------------------------------------------------------
bool nssf_config::parse_config() {
  YAML::Node config = {};
  try {
    auto nssf = std::dynamic_pointer_cast<nssf_config_type>(get_local());
    config    = YAML::LoadFile(nssf->get_slice_config_path());
  } catch (YAML::BadFile& e) {
    Logger::nssf_app().error(
        "The slice config file specified does not exist: %s", e.what());
    return false;
  }

  // Parse nsi_info_list
  if (config["configuration"]["nsiInfoList"]) {
    parse_nsi_info(config["configuration"]["nsiInfoList"], nssf_nsi_info);
  } else {
    Logger::nssf_app().error("Error parsing section : nsiInfoList");
    return false;
  }

  // Parse ta_info_list
  if (config["configuration"]["taInfoList"]) {
    parse_ta_info(config["configuration"]["taInfoList"], nssf_ta_info);
  } else {
    Logger::nssf_app().error("Error parsing section : taInfoList");
    return false;
  }

  // Parse amf_info_list
  if (config["configuration"]["amfInfoList"]) {
    parse_amf_info(config["configuration"]["amfInfoList"], nssf_amf_info);
  } else {
    Logger::nssf_app().error("Error parsing section : amfInfoList");
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
// bool nssf_config::get_slice_config(nlohmann::json& slice_config) {
//   slice_config = nssf_slice_config;
//   return true;
// }

//------------------------------------------------------------------------------
bool nssf_config::get_api_list(nlohmann::json& api_list) {
  api_list["OAI-NSSF"] = {
      {"Organisation", "Openairinterface Software Aliance"},
      {"Description", "OAI-NSSF initial Release"},
      {"Version", "1.0.0"},
      {"Supported APIs",
       {{"API", "Network Slice Information (Document)"},
        {"Method", "GET"},
        {"URI Path",
         "/nnssf-nsselection/<api_version>/network-slice-information"},
        {"Details",
         "Retrieve the Network Slice Selection Information (PDU Session)"}}}};
  return true;
}
bool nssf_config::init() {
  return config::init() && parse_config();
}
//------------------------------------------------------------------------------
