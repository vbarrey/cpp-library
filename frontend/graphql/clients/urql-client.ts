import { cacheExchange, createClient, fetchExchange } from "urql";

export const graphqlClient = createClient({
    url: "http://localhost:3000/api/graphql",

    exchanges: [
        cacheExchange,
        fetchExchange
    ]
});