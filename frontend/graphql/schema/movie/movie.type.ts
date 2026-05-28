export const movieTypeDefs = /* GraphQL */ `
    type Movie {
        id: ID!
        title: String!
        coverUrl: String
        description: String
        genres: [Genre!]
        rating: Float
        type: EnumMediaType
        director: String
        durationMinutes: Int
        releaseDate: String
        createdAt: String
        updatedAt: String
    }

    type PaginatedMovies {
        data: [Movie!]!
        total: Int!
        page: Int!
        limit: Int!
    }
`;