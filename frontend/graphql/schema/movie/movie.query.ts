export const movieQueryDefs = /* GraphQL */ `
    type Query {
        movies(page: Int = 1): PaginatedMovies!
        movie(id: ID!): Movie
    }
`;