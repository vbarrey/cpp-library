import { auth, signOut } from "@/src/auth";
import { redirect } from "next/navigation";

import {
  Card,
  CardContent,
  CardHeader,
  CardTitle,
  CardDescription,
  CardFooter,
} from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { AlertDialogDestructive } from "@/components/ui/alert-dialog-destructive";

async function logoutUser() {
  "use server";

  await signOut();

  redirect("/");
}

async function deleteUser() {
  console.log("delete")
}

export default async function ProfilePage() {
  const session = await auth();

  if (!session) {
    redirect("/login");
  }

  return (
    <main className="min-h-screen flex items-center justify-center px-4">
      <Card className="w-full max-w-md">
        <CardHeader>
          <CardTitle>
            Your profile
          </CardTitle>

          <CardDescription>
            Current authenticated user
          </CardDescription>
        </CardHeader>

        <CardContent className="space-y-4">
          <div>
            <p className="text-sm text-muted-foreground">
              ID
            </p>

            <p>{session.user.id}</p>
          </div>

          <div>
            <p className="text-sm text-muted-foreground">
              Name
            </p>

            <p>{session.user.name}</p>
          </div>

          <div>
            <p className="text-sm text-muted-foreground">
              Email
            </p>

            <p>{session.user.email}</p>
          </div>

          <div>
            <p className="text-sm text-muted-foreground">
              Role
            </p>

            <p>{session.user.role}</p>
          </div>
        </CardContent>

        <CardFooter>
          <Button
            variant="destructive"
            onClick={logoutUser}
          >
            Se déconnecter
          </Button>

          <AlertDialogDestructive
              buttonTitle="Delete Account"
              dialogTitle="Delete Account"
              dialogDescription="Are you sure you want to delete your account? This action cannot be undone."
              dialogCancel="Cancel"
              dialogAction="Delete"
              onConfirm={deleteUser}
          />
        </CardFooter>
      </Card>
    </main>
  );
}