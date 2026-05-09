import {LoginForm} from "./login-form"

import {
  Card,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";

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

        <LoginForm />
      </Card>
    </main>
  );
}