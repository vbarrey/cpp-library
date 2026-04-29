import Link from "next/link"
import { signIn } from "@/src/auth";

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

async function loginUser(
  formData: FormData
) {
  "use server";

  console.log("User logging in");

  await signIn("credentials", {
    email:
      formData.get("email"),
    password:
      formData.get("password"),
    redirectTo: "/profile",
    redirect: true,
  });
}

export default function LoginPage() {
  return (
    <main className="min-h-screen flex items-center justify-center px-4">
      <Card className="w-full max-w-md">
        <CardHeader>
          <CardTitle>
            Bon retour parmi nous!
          </CardTitle>

          <CardDescription>
            Connecte-toi à ton compte
          </CardDescription>
        </CardHeader>

        <form action={loginUser}>
          <CardContent className="space-y-6 pb-6">
            <div className="space-y-2">
              <Label htmlFor="email">
                Email
              </Label>

              <Input
                id="email"
                name="email"
                type="email"
                placeholder="example@mail.com"
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
              Se connecter
            </Button>

            <p className="text-center text-sm text-muted-foreground">
              Pas encore de compte?{" "}
              <Link
                href="/register"
                className="text-primary hover:underline"
              >
                S'inscrire
              </Link>
            </p>
          </CardFooter>
        </form>
      </Card>
    </main>
  );
}