import { GraphQLContext } from "../../context/create-context";

export const movieResolvers = {
    Query: {
        movies: async (
            _: unknown,
            args: { page: number },
            context: GraphQLContext
        ) => {
            return context.movieApi.getMovies(args.page);
        },

        movie: async (
            _: unknown,
            args: { id: string },
            context: GraphQLContext
        ) => {
            return context.movieApi.getMovie(args.id);
        }
    }
};