"use client"

import { useState } from "react";
import { redirect } from "next/navigation";
import Link from "next/link";

import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";

import {
  Input
} from "@/components/ui/input";

import {
  Label
} from "@/components/ui/label";

import {
  Button
} from "@/components/ui/button";
import { UsernameField } from "@/components/ui/username-field";

export default function RegisterPage() {
  const [registerError, setRegisterError] = useState("");

  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");

  const registerUser = async(formData: FormData) => {
    const response = await fetch(
    `${process.env.NEXT_PUBLIC_API_URL}/auth/register`,
    {
      method: "POST",
      headers: {
        "Content-Type":
          "application/json",
      },
      body: JSON.stringify({
        username:
          formData.get("username"),
        email:
          formData.get("email"),
        password:
          formData.get("password"),
      }),
    }
  );

  if (!response.ok) {
    let res = await response.json();
    setRegisterError(res.description);
    switch(res.trigger){
      case "email":
        
    }
    return;
  }

  redirect("/login");
  }

  return (
    <main className="min-h-screen flex items-center justify-center px-4">
      <Card className="w-full max-w-md">
        <CardHeader>
          <CardTitle>
            Faisons connaissance!
          </CardTitle>

          <CardDescription>
            Crée ton espace de lecture
          </CardDescription>
        </CardHeader>

        <form action={registerUser}>
          <CardContent className="space-y-6 pb-6">
            <div className="space-y-2">
              <Label htmlFor="username">
                Pseudo <span className="text-destructive">*</span>
              </Label>

              <UsernameField />
            </div>

            <div className="space-y-2">
              <Label htmlFor="email">
                Email <span className="text-destructive">*</span>
              </Label>

              <Input
                id="email"
                name="email"
                type="email"
                placeholder="your@mail.com"
                required
                value={email}
                onChange={(e)=>{setEmail(e.target.value);}}
              />
            </div>

            <div className="space-y-2">
              <Label htmlFor="password">
                Mot de passe <span className="text-destructive">*</span>
              </Label>

              <Input
                id="password"
                name="password"
                type="password"
                required
                value={password}
                onChange={(e)=>{setPassword(e.target.value);}}
              />
            </div>

            {registerError.length>0 && (
            <div className="text-center">
              <p className="text-sm text-destructive">{registerError}</p>
            </div>
          )}
          </CardContent>

          <CardFooter className="flex flex-col gap-4">
            <Button
              className="w-full"
              type="submit"
            >
              S'inscrire
            </Button>

            <p className="text-center text-sm text-muted-foreground">
              Déjà un compte?{" "}
              <Link
                href="/login"
                className="text-primary hover:underline"
              >
                Se connecter
              </Link>
            </p>
          </CardFooter>
        </form>
      </Card>
    </main>
  );
}