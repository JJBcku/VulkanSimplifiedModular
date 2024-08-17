%VULKAN_SDK%\Bin\glslc.exe basicVertexShader.vert -finvert-y -O -o basicVertexShader.vert.spv
%VULKAN_SDK%\Bin\glslc.exe basicFragmentShader.frag -O -o basicFragmentShader.frag.spv
%VULKAN_SDK%\Bin\glslc.exe basicVertexShader.vert -finvert-y -g -O0 -o basicVertexShader.debug.vert.spv
%VULKAN_SDK%\Bin\glslc.exe basicFragmentShader.frag -g -O0 -o basicFragmentShader.debug.frag.spv

%VULKAN_SDK%\Bin\glslc.exe basicVertexShader.vert -finvert-y -S -O -o basicVertexShader.vert.txt
%VULKAN_SDK%\Bin\glslc.exe basicFragmentShader.frag -S -O -o basicFragmentShader.frag.txt
%VULKAN_SDK%\Bin\glslc.exe basicVertexShader.vert -finvert-y -S -g -O0 -o basicVertexShader.debug.vert.txt
%VULKAN_SDK%\Bin\glslc.exe basicFragmentShader.frag -S -g -O0 -o basicFragmentShader.debug.frag.txt

pause