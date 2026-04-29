"use client";

import { useEffect, useState } from "react";
import {
  CheckIcon,
  XIcon,
  Loader2
} from "lucide-react";

import {
  InputGroup,
  InputGroupInput,
  InputGroupAddon,
} from "@/components/ui/input-group";

type Status =
  | "idle"
  | "checking"
  | "available"
  | "taken";

export function UsernameField() {
  const [username, setUsername] =
    useState("");

  const [status, setStatus] =
    useState<Status>("idle");

  useEffect(() => {
    if (!username.trim()) {
      setStatus("idle");
      return;
    }

    const timeout = setTimeout(
      async () => {
        setStatus("checking");

        const response =
          await fetch(
            `${process.env.NEXT_PUBLIC_API_URL}/auth/check-username?username=${encodeURIComponent(
              username
            )}`
          );

        const result =
          await response.json();


          console.log("result =>", result);
        if (result.available) {
          setStatus("available");
        } else {
          setStatus("taken");
        }
      },
      500
    );

    return () =>
      clearTimeout(timeout);
  }, [username]);

  return (
    <div className="space-y-2">
      <InputGroup>
        <InputGroupInput
          id="username"
          name="username"
          placeholder="my_username"
          value={username}
          onChange={(e) =>
            setUsername(e.target.value)
          }
        />

        <InputGroupAddon align="inline-end">
          {status === "checking" && (
            <Loader2 className="animate-spin size-4" />
          )}

          {status === "available" && (
            <CheckIcon className="size-4" />
          )}

          {status === "taken" && (
            <XIcon className="size-4" />
          )}
        </InputGroupAddon>
      </InputGroup>

      {status === "taken" && (
        <p className="text-sm text-destructive">
          Ce pseudo est déjà pris
        </p>
      )}
    </div>
  );
}