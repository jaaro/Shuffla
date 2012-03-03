//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http
{
namespace server2
{

request_handler::request_handler(const QueryDispatcher& doc_root)
    : doc_root_(doc_root)
{
}

void request_handler::handle_request(const request& req, reply& rep)
{
    // Decode url to path.
    std::string request_path;
    if (!url_decode(req.uri, request_path)) {
        rep = reply::stock_reply(reply::bad_request);
        return;
    }

    // Request path must be absolute and not contain "..".
    if (request_path.empty() || request_path[0] != '/'
            || request_path.find("..") != std::string::npos) {
        rep = reply::stock_reply(reply::bad_request);
        return;
    }

    std::string response = doc_root_.process_query(request_path);

    rep.content.append(response.c_str(), response.size());
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type("txt");
}

bool request_handler::url_decode(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    return true;
}

} // namespace server2
} // namespace http

