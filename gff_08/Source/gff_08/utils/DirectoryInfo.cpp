// Fill out your copyright notice in the Description page of Project Settings.

#include "DirectoryInfo.h"

#include <fstream>
#include <sstream>
#include <string>

FString UDirectoryInfo::HelloWorld() {
	return FString("Hello World!");
}

bool UDirectoryInfo::WriteFragCount(FString fileName, TArray<int> counter) {
	//�f�B���N�g���擾
	FString dir = FPaths::LaunchDir();
	//�t�@�C�����擾
	FString fName = fileName + ".txt";

	FString fullPath = dir + "/" + fName;

	std::wstring strFilePath(TCHAR_TO_WCHAR(*fullPath));
	std::vector<std::wstring> vfile;
	std::wifstream ifs(strFilePath, std::ios::in);

	if (ifs.is_open() == false) {
		UE_LOG(LogTemp, Warning, TEXT("Create new file : %s"), *fullPath);
		vfile.push_back(L"1");
	} else {
		//���Ƀt�@�C��������Ȃ�A���̒��g���擾����
		std::wstring line = L"";
		while (std::getline(ifs, line)) {
			vfile.push_back(line);
		}
		//�Q�[���񐔂𑝂₷
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
	//�O�ԖڂɌÂ������폜
	if (vfile.size() >= 7) {
		vfile.erase(vfile.begin() + 3);
	}

	for (auto& f : vfile) {
		ofs << f << std::endl;
	}
	ofs.close();
	return true;
}
