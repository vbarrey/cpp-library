import { createSchema } from "graphql-yoga";

import { movieTypeDefs } from "./schema/movie/movie.type";
import { movieQueryDefs } from "./schema/movie/movie.query";
import { movieResolvers } from "./schema/movie/movie.resolver";
import { mediaEnumDefs } from "./schema/media/media.enum";
import { genreTypeDefs } from "./schema/media/genre.type";

export const schema = createSchema({
    typeDefs: `
        ${mediaEnumDefs}
        ${genreTypeDefs}
        ${movieTypeDefs}
        ${movieQueryDefs}
    `,
    resolvers: [
        movieResolvers
    ]
});