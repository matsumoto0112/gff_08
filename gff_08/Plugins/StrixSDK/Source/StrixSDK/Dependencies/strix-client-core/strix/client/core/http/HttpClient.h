#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace strix { namespace client { namespace core { namespace http {

/**
 *  HTTP request consisting of header information, content, request method, and URL
 */
struct HttpRequest
{
	std::map<std::string, std::string> m_headers;
	std::vector<uint8_t> m_content;
	std::string m_actionType;
	std::string m_url;
};

/**
 *  Response to an HTTP request, containing headers, content, and response status code.
 *  Content is in the form of a vector of bytes
 */
struct BytesHttpResponse
{
	std::map<std::string, std::string> m_headers;
	std::vector<uint8_t> m_content;
	int m_code;
};

/**
 *  Response to an HTTP request, containing headers, content, and response status code.
 *  Content is in the form of a string
 */
struct StringHttpResponse
{
	std::map<std::string, std::string> m_headers;
	std::string m_content;
	int m_code;
};

typedef std::function<void(BytesHttpResponse)> BytesHttpResultHandler;
typedef std::function<void(StringHttpResponse)> StringHttpResultHandler;

/**
 *  Client controller for HTTP Requests
 */
class HttpClient
{
public:
	virtual ~HttpClient() = default;

	/**
	 *  Make an HTTP request. The handler will be called on a response
	 *  @param	request	The HTTP request
	 *  @param	resultHandler	The handler to be called on response
	 */
	virtual bool Request(HttpRequest& request, BytesHttpResultHandler resultHandler) = 0;

	/**
	 *  Make an HTTP request. The handler will be called on a response
	 *  @param	request	The HTTP request
	 *  @param	resultHandler	The handler to be called on response
	 */
	virtual bool Request(HttpRequest& request, StringHttpResultHandler resultHandler) = 0;
};

typedef std::shared_ptr<HttpClient> HttpClientPtr;

} } } }
