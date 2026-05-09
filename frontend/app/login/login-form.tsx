"use client";

import { useActionState } from "react";
import { loginUser } from "./action";

import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { CardContent, CardFooter } from "@/components/ui/card";
import Link from "next/link";

export function LoginForm() {
    const [state, action, isPending] = useActionState(loginUser, null);

    return (
        <form action={action}>
            <CardContent className="space-y-6 pb-6">
                <div className="space-y-2">
                    <Label htmlFor="email">
                        Email
                    </Label>

                    <Input id="email" name="email" type="email" placeholder="example@mail.com"/>
                </div>

                <div className="space-y-2">
                    <Label htmlFor="password">
                        Mot de passe
                    </Label>

                    <Input id="password" name="password" type="password"/>
                </div>

                {state?.error && (
                    <div className="text-center">
                        <p className="text-sm text-destructive">
                            {state.error}
                        </p>
                    </div>
                )}

            </CardContent>

            <CardFooter className="flex flex-col gap-4">
                <Button className="w-full" type="submit" disabled={isPending} >
                    Se connecter
                </Button>

                <p className="text-center text-sm text-muted-foreground">
                    Pas encore de compte?{" "}
                    <Link href="/register" className="text-primary hover:underline">
                        S'inscrire
                    </Link>
                </p>
            </CardFooter>
        </form>
    );
}