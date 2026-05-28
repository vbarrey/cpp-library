import type { CodegenConfig } from "@graphql-codegen/cli";

const config: CodegenConfig = {
    schema: "http://localhost:3000/api/graphql",

    documents: [
        "graphql/operations/**/*.graphql"
    ],

    generates: {
        "./graphql/generated/graphql.ts": {
            plugins: [
                "typescript",
                "typescript-operations",
                "typed-document-node"
            ]
        }
    }
};

export default config;