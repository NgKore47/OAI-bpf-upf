# RELEASE NOTES: #

## v2.0.0 -- December 2023 ##

* Features
  - Support YAML configuration file
    * Yaml validation default value
  - Add support for traffic steering rules
  - Add support for redirection rules
* Fixes
  - Handling boolean values in yaml parsing for policies
* Tech debt
  - Updated common models to 3GPP TS 29.571 Release 16.13.0 and moved them to the shared common submodule
  - Updated PCF models to Release 16.17.0 and moved them to the shared common submodule
  - Switching to clang-format-12
  - Published image on Docker-Hub is using now Ubuntu-22 as base image
    * Ubuntu-18 is no longer supported

## v1.5.1 -- May 2023 ##

* Add HTTP/2 support
* Code Refactoring for:
  * Logging mechanism (runtime log level selection)
  * Installation / build scripts
  * Continuous Integration scripts
* Published image on Docker-Hub is using now Ubuntu-20 as base image
  * We will soon obsolete the build system for Ubuntu18.04

## v1.5.0 -- January 2023 ##

* Initial release
* NRF registration
* Add Npcf_SMPolicyControl API Create, Update, Delete and Get procedures
* Add file based policy provisioning
* Add policy decision feature based on SUPI, DNN, Slice and default policy
* Fixed docker exit by catching SIGTERM
* release mode does not use libasan anymore --> allocation of 20T virtual memory is no longer done

