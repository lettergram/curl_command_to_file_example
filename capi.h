#ifndef CAPI_H
#define CAPI_H

#include <iostream>
#include <string>

#include <stdio.h>
#include <curl/curl.h>

class capi {

 public:
  capi(std::string base_url);
  ~capi();

  /* REST API Calls */
  std::string get(std::string end_point);
  std::string post(std::string end_point);
  std::string patch(std::string end_point, std::string data);
  
  
  /* Get/Set */    
  void set_base_url(std::string base_url);
  std::string get_base_url();
  
  void set_auth_token(std::string token);
  std::string get_auth_token();
  
  void set_obj_id(std::string id);
  std::string get_obj_id();
  
 private:
  std::string root_url;
  std::string auth_token;
  std::string obj_id;
};

#endif // CAPI_H
