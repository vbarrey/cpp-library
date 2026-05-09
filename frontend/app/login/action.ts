"use server"

import { AuthError } from "next-auth";
import { signIn }  from "@/src/auth";

export async function loginUser(
    prevState: any,
    formData: FormData
) {
    try {
        await signIn("credentials", {
            email: formData.get("email"),
            password: formData.get("password"),
            redirectTo: "/profile",
            redirect: true,
        });

        return null;
    } catch (error) {
        if (error instanceof AuthError) {
            switch (error.type) {
                case "CredentialsSignin":
                    return {
                        error: "Email ou mot de passe incorect"
                    };
                default:
                    return {
                        error: "Une erreur est survenue"
                    };
            };
        }
        throw error;
    }
}