export module RunProgram.CreatePipeline;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.SharedData;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;
import VulkanData.PipelineLayoutData;
import VulkanData.PipelinesList;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.SharedPipelineData.Data;

export void CreatePipeline(VulkanData& data, std::uint32_t width, std::uint32_t height);