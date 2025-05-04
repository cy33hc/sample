#include <dlfcn.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "sceAppInstUtil.h"

int main()
{
	int ret = sceAppInstUtilInitialize();
	if(ret){
	   printf("sceAppInstUtilInitialize failed: 0x%08X\n", ret);
	   return -1;
	}
	
	PlayGoInfo arg3;
	SceAppInstallPkgInfo pkg_info;
	(void)memset(&arg3, 0, sizeof(arg3));
	
	for (size_t i = 0; i < NUM_LANGUAGES; i++) {
		strncpy(arg3.languages[i], "", sizeof(arg3.languages[i]) - 1);
	}
	
	for (size_t i = 0; i < NUM_IDS; i++) {
		 strncpy(arg3.playgo_scenario_ids[i], "",
					sizeof(playgo_scenario_id_t) - 1);
		 strncpy(*arg3.content_ids, "", sizeof(content_id_t) - 1);
	}
	
	MetaInfo in = {
		.uri = "/data/ps4_smb_client.pkg",
		.ex_uri = "",
		.playgo_scenario_id = "",
		.content_id = "",
		.content_name = "PKG TITLE",
		.icon_url = ""
	};
	
	int num = sceAppInstUtilInstallByPackage(&in, &pkg_info, &arg3);
	if (num == 0) {
		puts("Download and Install console Task initiated");
	} else {
		printf("DPI: Install failed with error code %d\n", num);
	}
	float prog = 0;
	SceAppInstallStatusInstalled status;
	
	while (strcmp(status.status, "playable") != 0) {
		sceAppInstUtilGetInstallStatus(pkg_info.content_id, &status);
		
		if (status.total_size != 0) {
			prog = ((float)status.downloaded_size / status.total_size) * 100.0f;
		}
	
		printf("DPI: Status: %s | error: %d | progress %.2f%% (%llu/%llu)\n", 
				   status.status, status.error_info.error_code, 
				   prog, status.downloaded_size, status.total_size);
	}
	return 0;
}
