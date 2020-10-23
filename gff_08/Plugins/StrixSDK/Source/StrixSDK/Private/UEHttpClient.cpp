/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "UEHttpClient.h"

UEHttpClient::UEHttpClient() : m_httpModule(&FHttpModule::Get()) {}

bool UEHttpClient::Request(strix::client::core::http::HttpRequest & request, strix::client::core::http::BytesHttpResultHandler resultHandler)
{
	TSharedRef<IHttpRequest> httpRequest = PrepareRequestBase(request);

	httpRequest->OnProcessRequestComplete().BindLambda(
		[resultHandler](FHttpRequestPtr requestPtr, FHttpResponsePtr response, bool wasSuccessful) {
		strix::client::core::http::BytesHttpResponse bytesResponse;
		bytesResponse.m_code = response->GetResponseCode();

		for (uint8 byte : response->GetContent())
		{
			bytesResponse.m_content.push_back(byte);
		}

		for (FString header : response->GetAllHeaders())
		{
			int32 splitterIndex = 0;
			if (header.FindChar(':', splitterIndex))
			{
				FString key = header.Left(splitterIndex);
				FString value = header.Right(header.Len() - (splitterIndex));
				bytesResponse.m_headers.insert(std::make_pair(TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value)));
			}
		}
		resultHandler(bytesResponse);
	});

	return httpRequest->ProcessRequest();
}

bool UEHttpClient::Request(strix::client::core::http::HttpRequest & request, strix::client::core::http::StringHttpResultHandler resultHandler)
{
	TSharedRef<IHttpRequest> httpRequest = PrepareRequestBase(request);

	httpRequest->OnProcessRequestComplete().BindLambda(
		[resultHandler](FHttpRequestPtr requestPtr, FHttpResponsePtr response, bool wasSuccessful) {
		strix::client::core::http::StringHttpResponse stringResponse;
		stringResponse.m_code = response->GetResponseCode();
		stringResponse.m_content = TCHAR_TO_UTF8(*(response->GetContentAsString()));

		for (FString header : response->GetAllHeaders())
		{
			int32 splitterIndex = 0;
			if (header.FindChar(':', splitterIndex))
			{
				FString key = header.Left(splitterIndex);
				FString value = header.Right(header.Len() - (splitterIndex));
				stringResponse.m_headers.insert(std::make_pair(TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value)));
			}
		}
		resultHandler(stringResponse);
	});

	return httpRequest->ProcessRequest();
}

TSharedRef<IHttpRequest> UEHttpClient::PrepareRequestBase(strix::client::core::http::HttpRequest & request)
{
	TSharedRef<IHttpRequest> httpRequest = m_httpModule->CreateRequest();
	httpRequest->SetURL(FString(request.m_url.c_str()));
	httpRequest->SetVerb(FString(request.m_actionType.c_str()));

	TArray<uint8> content;
	content.Append(&request.m_content[0], request.m_content.size());
	httpRequest->SetContent(content);

	for (std::pair<std::string, std::string> header : request.m_headers)
	{
		httpRequest->SetHeader(FString(header.first.c_str()), FString(header.second.c_str()));
	}

	return httpRequest;
}
