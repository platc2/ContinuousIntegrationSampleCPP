#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <vulkan/vulkan.h>


int main()
{
	std::uint32_t uiLayerPropertiesCount = 0;
	vkEnumerateInstanceLayerProperties(&uiLayerPropertiesCount, nullptr);
	std::vector<VkLayerProperties> vecInstanceLayerProperties(uiLayerPropertiesCount);
	vkEnumerateInstanceLayerProperties(&uiLayerPropertiesCount, vecInstanceLayerProperties.data());

	std::cout << "--=/ Vulkan Layers \\=--\n";
	std::for_each(vecInstanceLayerProperties.begin(), vecInstanceLayerProperties.end(), [](const VkLayerProperties& xLayerProperties)
	{
		std::cout << "\t" << xLayerProperties.layerName << "\n";
	});
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
