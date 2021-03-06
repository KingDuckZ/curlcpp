/* 
 * File:   curl_header.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:45 PM
 */

#include "curl_header.h"
#include <algorithm>

using std::for_each;
using curl::curl_header;

// Implementation of constructor
curl_header::curl_header(const size_t header_num) {
    curl_header();
    this->setSize(header_num);
}

// Implementation of destructor
curl_header::~curl_header() {
    curl_slist_free_all(this->headers);
    this->headers = nullptr;
}

// Implementation of setHeader method
void curl_header::set(const string header) {
    this->headers = curl_slist_append(this->headers,header.c_str());
    if (this->headers == nullptr) {
        throw curl_error(" *** An error occurred while inserting last header ***",__FUNCTION__);
    }
}

// Implementation of setHeadersSize method
void curl_header::setSize(const size_t headers_num) {
    if (headers_num > 0) {
        if (headers_num != this->tmpHeaders.size()) {
            this->tmpHeaders.resize(headers_num);
        }
    } else {
        throw curl_error(" *** Headers vector size cannot be less or equal to zero ***",__FUNCTION__);
    }
}

// Implementation of add method
void curl_header::add(const vector<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
}

// Implementation of add overloaded method
void curl_header::add(const list<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
}

// Implementation of add overloaded method
void curl_header::add(const string header) {
    this->tmpHeaders.push_back(header);
}

// Implementation of remve method
void curl_header::remove(const string remove) {
    for (vector<string>::iterator it = this->tmpHeaders.begin(); it != this->tmpHeaders.end(); ++it) {
        if ((*it) == remove) {
            this->tmpHeaders.erase(it);
            break;
        }
    }
}

// Implementation of confirm method
void curl_header::confirm() {
    for_each(this->tmpHeaders.begin(),this->tmpHeaders.end(),[this](const string header) { this->set(header); } );
}

// Implementation of getHeader method
const vector<string> curl_header::get() const {
    return this->tmpHeaders;
}