import { MovieApiClient } from "../clients/movie-api.client";

export interface GraphQLContext {
    movieApi: MovieApiClient;
}

export async function createContext(): Promise<GraphQLContext> {
    return {
        movieApi: new MovieApiClient()
    };
}