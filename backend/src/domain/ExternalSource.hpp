#pragma once

#include <string>

enum class ExternalSource
{
	TMDb
};

inline std::string externalSourceToString(const ExternalSource& extSrc)
{
	switch (extSrc) {
	case ExternalSource::TMDb:
		return "TMDb";
	default:
		return "";
	}
}