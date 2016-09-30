if os.is("macosx") then
    premake.tools.gcc.ldflags.flags = nil
end

solution "tlvm"
    configurations { "Debug", "Release" }
    includedirs { "include", 
                  "tlvm/include",
                  "tlvm/src/include" }
    files { "include/**.h" }

    defines { "TLVM_BUILD" }
    
    tlvmcpus = {
       cpu_8080 = true,
       cpu_6800 = false,
    }
    
    for cpu,x in pairs(tlvmcpus) do 
       if x then
          defines {  "TLVM_HAS_" .. cpu:gsub("cpu_", "") }
       end
    end

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
        targetdir "build/debug"
        
    configuration "Release"
        defines { "NDEBUG" }
        optimize "Size"
        warnings "Extra"
        flags { "FatalWarnings",
                "NoFramePointer" }
        targetdir "build/release"

    dofile("tlvm/buildlib.lua")

    project "imsai"
    language "C"
    kind "ConsoleApp"
    files { "src/**.c" }
    links { "tlvm" }


