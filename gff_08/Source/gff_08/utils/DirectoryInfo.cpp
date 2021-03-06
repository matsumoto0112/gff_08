// Fill out your copyright notice in the Description page of Project Settings.

#include "DirectoryInfo.h"

#include <fstream>
#include <sstream>
#include <string>

FString UDirectoryInfo::HelloWorld() {
	return FString("Hello World!");
}

bool UDirectoryInfo::WriteFragCount(FString fileName, TArray<int> counter) {
	//ディレクトリ取得
	FString dir = FPaths::LaunchDir();
	//ファイル名取得
	FString fName = fileName + ".txt";

	FString fullPath = dir + "/" + fName;

	std::wstring strFilePath(TCHAR_TO_WCHAR(*fullPath));
	std::vector<std::wstring> vfile;
	std::wifstream ifs(strFilePath, std::ios::in);

	if (ifs.is_open() == false) {
		UE_LOG(LogTemp, Warning, TEXT("Create new file : %s"), *fullPath);
		vfile.push_back(L"1");
	} else {
		//既にファイルがあるなら、その中身を取得する
		std::wstring line = L"";
		while (std::getline(ifs, line)) {
			vfile.push_back(line);
		}
		//ゲーム回数を増やす
		int count = _wtoi(vfile[0].c_str());
		count++;
		std::wostringstream oss;
		oss << count;
		vfile[0] = oss.str();
	}
	ifs.close();

	std::wostringstream oss;
	for (auto& c : counter) {
		oss << c << ",";
	}
	vfile.push_back(oss.str());

	std::wofstream ofs(strFilePath);
	//三番目に古い情報を削除
	if (vfile.size() >= 7) {
		vfile.erase(vfile.begin() + 3);
	}

	for (auto& f : vfile) {
		ofs << f << std::endl;
	}
	ofs.close();
	return true;
}
