"use client";

import { Provider } from "urql";

import { graphqlClient } from "@/graphql/clients/urql-client";

interface GraphQLProviderProps {
    children: React.ReactNode;
}

export function GraphQLProvider({
    children
}: GraphQLProviderProps) {
    return (
        <Provider value={graphqlClient}>
            {children}
        </Provider>
    );
}