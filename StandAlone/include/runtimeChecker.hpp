#pragma once
#include <string>
#include <optional>
#include <filesystem>
#include <vector>


#ifdef OS_WINDOWS
#include <Windows.h>
    using RUNNER_INFO = PROCESS_INFORMATION;
#else
    #include <dlfcn.h>
    #include <spawn.h>
    using RUNNER_INFO = pid_t;
#endif





using MAYBE_RUNNER = std::optional<RUNNER_INFO>;
namespace fs = std::filesystem; 

enum SupportedRuntimes {
    CUDA,
    HIP,
    METAL,
    OPENCL,
    OPENMP,
    SERVER,
    SERIAL,
    CUSTOM
};

using STRVEC    = std::vector<std::string>;
using PATH      = std::pair<SupportedRuntimes, std::string>;
using MAYBE_PATH= std::optional<PATH>;







namespace RuntimeCheck{
    bool isAvailable(PATH& path);
    bool ExcuteRunner(const std::string& executePath, const int& portNum);
};

//Calculation fallback lists.
struct FallbackList{
public:
    //checked first, reads from back. put excutable cudaRun's directory path here
    STRVEC CUDAFallback = {"./"};

    STRVEC HIPFallback = {"./"};

    STRVEC METALFallback = {"./"};
    //reads from back. put excutable openclRun's directory path here
    STRVEC OpenCLFallback = {"./"};

    //reads from back. put excutable openmpRun's directory path here
    STRVEC OpenMPFallback = {"./"};

    STRVEC ServerFallback;
    //checked fourth, reads from back. put server IP or URL here, server should manually run STFT runtimes. 
    
    STRVEC SerialFallback = {"./"};

    STRVEC CustomFallback = {"./"};

    MAYBE_PATH  getNext();
private:
    template <SupportedRuntimes Type>
    bool VectorITR(STRVEC& vec, PATH& result);
};

template<SupportedRuntimes Type>
inline
bool
FallbackList::VectorITR(STRVEC& vec, PATH& result)
{
    if(vec.empty())
    {
        return false;
    }
    else
    {
        auto path = vec.back();
        vec.pop_back();
        result.first = Type;
        result.second = path;
        return true;
    }
}


template<>
inline
bool
FallbackList::VectorITR<SupportedRuntimes::SERVER>(STRVEC& vec, PATH& result)
{
    
    if(vec.empty())
    {
        return false;
    }
    else
    {
        auto path = vec.back();
        vec.pop_back();
        result.first = SERVER;
        result.second = path;
        return true;
    }
}
