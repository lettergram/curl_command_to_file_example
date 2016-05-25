#include "capi.h"

/* Helper for writebacks */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

capi::capi(std::string base_url){
    root_url = base_url;
}

capi::~capi(){
    // Nothing
}

/**
 * GET API call from an endpoint
 *
 * The end point being an extension of the base url
 *
 * set via the constructor or set_base_url(std::string base_url)
 *
 * EXAMPLE: www.test.com/<end_point>
 * 
 * If a specific item/object id is being searched for,
 * set it prior to use, using set_obj_id(std::string obj_id)
 * 
 * EXAMPLE CASE: www.test.com/<end_point>/<obj_id>.json
 *
 * obj_id could be a record or user.
 *
 * Similarly, set any auth_token to the API prior to use, 
 * using set_auth_token(std::string auth_token)
 *
 */
std::string capi::get(std::string end_point){

    CURLcode ret;
    CURL *hnd;

    struct curl_slist *slist1;

    std::string auth_header = "Authorization: Token token=\"" + auth_token + "\"";
    std::string url = root_url + "/" + end_point;
    if(!obj_id.empty()){ url = url + "/" + obj_id; }
    std::string readBuffer;

    /* Create header */
    slist1 = NULL;
    slist1 = curl_slist_append(slist1, auth_header.c_str());

    /* Initialize curl GET request */
    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
    curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.43.0");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

    /* Write response to readBuffer */
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

    /* Perform API request */
    ret = curl_easy_perform(hnd);

    /* Obtain response code */
    long http_code = 0;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &http_code);

    /* Clean up curl */
    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;

    return readBuffer;
}

/**
 * POST API call from an endpoint
 *
 * The end point being an extension of the base url
 *
 * set via the constructor or set_base_url(std::string base_url)
 *                          
 * EXAMPLE: www.test.com/<end_point>
 *                                                      
 * If a specific item/object id is being searched for
 * set it prior to use, using set_obj_id(std::string obj_id)
 *
 * EXAMPLE CASE: www.test.com/<end_point>/<obj_id>.json
 *
 * obj_id could be a record or user. 
 *                                  
 * Similarly, set any auth_token to the API prior to use 
 * using set_auth_token(std::string auth_token)
 *
 */
std::string capi::post(std::string end_point){

    CURLcode ret;
    CURL *hnd;

    struct curl_slist *slist1;

    std::string auth_header = "Authorization: Token token=\"" + auth_token + "\"";
    std::string url = root_url + "/" + end_point;
    std::string readBuffer;

    slist1 = NULL;
    slist1 = curl_slist_append(slist1, auth_header.c_str());

    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
    curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.43.0");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

    /* Perform API request */
    ret = curl_easy_perform(hnd);

    /* Obtain response code */
    long http_code = 0;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &http_code);

    /* Clean up curl */
    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;

    return readBuffer;
}

/** 
 * PATCH API call from an endpoint
 *                                                         
 * The end point being an extension of the base url
 *
 * set via the constructor or set_base_url(std::string base_url)
 *                          
 * EXAMPLE: www.test.com/<end_point>
 *
 * If a specific item/object id is being searched for
 * set it prior to use, using set_obj_id(std::string obj_id)
 *                               
 * EXAMPLE CASE: www.test.com/<end_point>/<obj_id>.json
 *                                    
 * obj_id could be a record or user.
 * 
 * Similarly, set any auth_token to the API prior to use 
 * using set_auth_token(std::string auth_token)
 *
 */
std::string capi::patch(std::string end_point, std::string data){

    CURLcode ret;
    CURL *hnd;

    struct curl_httppost *post1;
    struct curl_httppost *postend;
    struct curl_slist *slist1;

    std::string auth_header = "Authorization: Token token=\"" + auth_token + "\"";
    std::string url = root_url + "/" + end_point + "/" + obj_id;
    std::string readBuffer;

    post1 = NULL;
    postend = NULL;
    curl_formadd(&post1, &postend,
               CURLFORM_COPYNAME, "data",
               CURLFORM_COPYCONTENTS, data.c_str(),
               CURLFORM_END);
    slist1 = NULL;
    slist1 = curl_slist_append(slist1, auth_header.c_str());

    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
    curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(hnd, CURLOPT_HTTPPOST, post1);
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.43.0");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

    /* Perform API request */
    ret = curl_easy_perform(hnd);

    /* Obtain response code */
    long http_code = 0;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_formfree(post1);
    post1 = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;

    return readBuffer;
}

/** Get/Set the base url **/
void capi::set_base_url(std::string base_url){ root_url = base_url; }
std::string capi::get_base_url(){ return root_url; }

/** Get/Set authorization tokens for API calls **/
void capi::set_auth_token(std::string token){ auth_token = token; }
std::string capi::get_auth_token(){ return auth_token; }

/** Get/Set the obj_id for GET call, i.e. www.test.com/item/<obj_id>.json **/
void capi::set_obj_id(std::string id){ obj_id = id; }
std::string capi::get_obj_id(){ return obj_id; }
