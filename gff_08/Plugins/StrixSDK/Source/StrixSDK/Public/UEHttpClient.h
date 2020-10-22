/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "Http.h"

#include <strix/client/core/http/HttpClient.h>

/** Strix HTTP client interface implementation that uses Unreal HTTP module.
 *  Requires the Unreal HTTP module to work.
 */
class UEHttpClient : public strix::client::core::http::HttpClient
{
public:
	UEHttpClient();

	/** Begin processing the request (with raw bytes as the result)
	 *  @param	request	The request to process
	 *  @param	resultHandler	The result handler to call when the request is completed
	 *  @return Whether the request was successfully started
	 */
	bool Request(strix::client::core::http::HttpRequest& request, strix::client::core::http::BytesHttpResultHandler resultHandler) override;

	/** Begin processing the request (with string as the result)
	 *  @param	request	The request to process
	 *  @param	resultHandler	The result handler to call when the request is completed
	 *  @return Whether the request was successfully started
	 */
	bool Request(strix::client::core::http::HttpRequest& request, strix::client::core::http::StringHttpResultHandler resultHandler) override;

private:
	/** Internal function for creating the Unreal HTTP request skeleton
	 *  @param	request	The request to use
	 *  @return Created request
	 */
	TSharedRef<IHttpRequest> PrepareRequestBase(strix::client::core::http::HttpRequest& request);

	FHttpModule* m_httpModule;
};
