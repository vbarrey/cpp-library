#pragma once

#include <pqxx/pqxx>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct Genre {
	std::string id;
	std::string name;

	static std::vector<Genre> mapGenreRow(pqxx::row_ref row) {
		auto genresJson = nlohmann::json::parse(row["genres"].c_str());

		std::vector<Genre> genres;

		for (const auto& g : genresJson) {
			genres.push_back(
				Genre{
					g["id"].get<std::string>(),
					g["name"].get<std::string>()
				}
			);
		}

		return genres;
	}
};

inline void to_json(nlohmann::json& j, const Genre& g)
{
	j = nlohmann::json{
		{"id", g.id},
		{"name", g.name}
	};
}

inline void from_json(const nlohmann::json& j, Genre& g)
{
	j.at("id").get_to(g.id);
	j.at("name").get_to(g.name);
}