#pragma once

#include <memory>
#include <expected>
#include "ISeriesRepository.hpp"
#include "../domain/DomainError.hpp"
#include "../domain/Result.hpp"
#include "../domain/Paginated.hpp"

class SeriesService {
public:
    explicit SeriesService(std::unique_ptr<ISeriesRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<std::vector<Series>> getAllSeries() {
        return repository->findAll();
    }

    Result<Paginated<Series>> getPaginatedSeries(int page, int limit) {
        int offset = (page - 1) * limit;

        auto series = repository->findPaginated(limit, offset);
        if (!series) return std::unexpected(series.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return Paginated<Series>{
            series.value(),
            total.value(),
            page,
            limit
        };
    }

    Result<Series> createSeries(const Series& series) {
        auto validation = validate(series);
        if (!validation) {
            return std::unexpected(validation.error());
        }

        return repository->create(series);
    }

private:
    std::unique_ptr<ISeriesRepository> repository;

    VoidResult validate(const Series& series) {
        if (series.media.title.empty()) {
            return std::unexpected(DomainError{ "Le titre est obligatoire" });
        }
        return {};
    }
};