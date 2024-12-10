
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "AES.h"
#include "../com/com.h"

using CString = const std::string&;
using String = std::string;

static inline std::vector<String> buildArgs();

int main(int argc, const char* argv[]){
    if(argc == 1){
        auto args = buildArgs();
        std::vector<const char*> argvs;
        argvs.resize(args.size());
        //const char* argvs[args.size()];
        for(int i = 0 ; i < (int)args.size() ; i ++){
            argvs[i] = args[i].c_str();
        }
        return main(args.size(), argvs.data());
    }
    //xx <in_file> <out_file>
    if(argc < 3){
        fprintf(stderr, "xx <in_file> <out_file>\n");
        return 1;
    }
    String inFile = argv[1];
    String outFile = argv[2];
    auto cs = EncDecPy::getFileContent0(inFile);
    if(cs.empty()){
        fprintf(stderr, "open input failed: %s\n", inFile.data());
        return 1;
    }
    String key1 = "@(**^$$%&)((&^^(";
    String key2 = "8g77d7fg7&%%(*^^";
    String content;
    //getFileContent0(arg)
    {
        med_ed::AES aes(8, 2 << 20);
        content = aes.cfb128(cs, key1, key2, true);
    }
    if(content.empty()){
        fprintf(stderr, "enc failed, infile = %s\n", inFile.data());
        return 1;
    }
    std::ofstream fos;
    fos.open(outFile.data(), std::ios::binary);
    if(!fos.is_open()){
        fprintf(stderr, "open output failed: %s\n", outFile.data());
        return 1;
    }
    fos.write(content.data(), content.length());
    return 0;
}

std::vector<String> buildArgs(){
    String mdDir = "/media/heaven7/Elements_SE/temp";
    String inFile = mdDir + "/libaisdk.so";
    String outFile = mdDir + "/libaisdk.so.enc";
    std::vector<String> args = {
        "modelM",
        inFile,
        outFile,
    };
    return args;
}
