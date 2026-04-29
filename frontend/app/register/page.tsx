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

async function registerUser(
  formData: FormData
) {
  "use server";

  const response = await fetch(
    "http://localhost:18080/auth/register",
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
    throw new Error(
      "Registration failed"
    );
  }

  redirect("/login");
}

export default function RegisterPage() {
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
                Pseudo
              </Label>

              <Input
                id="username"
                name="username"
                placeholder="Victor"
              />
            </div>

            <div className="space-y-2">
              <Label htmlFor="email">
                Email
              </Label>

              <Input
                id="email"
                name="email"
                type="email"
                placeholder="victor@mail.com"
              />
            </div>

            <div className="space-y-2">
              <Label htmlFor="password">
                Mot de passe
              </Label>

              <Input
                id="password"
                name="password"
                type="password"
              />
            </div>
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