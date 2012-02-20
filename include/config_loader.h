#ifndef CONFIGLOADER_H_
#define CONFIGLOADER_H_

#include <string>

class ConfigLoader {
public:
	ConfigLoader();
	virtual ~ConfigLoader();

	void load_config(const std::string& path);
};

#endif /* CONFIGLOADER_H_ */
