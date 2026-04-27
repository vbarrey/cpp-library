import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";
import Link from "next/link";

import {
  NavigationMenu,
  NavigationMenuContent,
  NavigationMenuItem,
  NavigationMenuLink,
  NavigationMenuList,
  NavigationMenuTrigger,
  navigationMenuTriggerStyle
} from "@/components/ui/navigation-menu"

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Cpp library",
  description: "A simple library management application built with Next.js and C++",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html
      lang="en"
      className={`${geistSans.variable} ${geistMono.variable} h-full antialiased`}
    >
      <body className={geistSans.className}>
        <div className="flex items-center justify-left">
          <h2 className="text-2xl font-bold p-4">Cpp library</h2>
          <NavigationMenu>
            <NavigationMenuList>
              <NavigationMenuItem>
                <NavigationMenuLink asChild>
                  <Link href="/">Accueil</Link>
                </NavigationMenuLink>
              </NavigationMenuItem>
              <NavigationMenuItem>
                <NavigationMenuTrigger>Livres</NavigationMenuTrigger>
                <NavigationMenuContent>
                  <ul className="grid w-[400px] gap-2 md:w-[500px] md:grid-cols-2 lg:w-[600px]">
                    <li>
                      <NavigationMenuLink asChild>
                        <Link href="/books" className="block space-y-1 rounded-md p-3">
                          <div className="flex flex-col gap-1 text-sm">
                            <div className="text-sm font-semibold">
                              Voir tous les livres
                            </div>
                            <p className="text-sm text-muted-foreground">
                              Consultez la liste complète de nos livres
                            </p>
                          </div>
                        </Link>
                      </NavigationMenuLink>
                    </li>
                    <li>
                      <NavigationMenuLink asChild>
                        <Link href="/authors" className="block space-y-1 rounded-md p-3">
                          <div className="flex flex-col gap-1 text-sm">
                            <div className="text-sm font-medium">
                              Voir tous les auteurs
                            </div>
                            <p className="text-sm text-muted-foreground">
                              Consultez la liste complète de nos livres classés par auteur
                            </p>
                          </div>
                        </Link>
                      </NavigationMenuLink>
                    </li>
                    <li>
                      <NavigationMenuLink asChild>
                        <Link href="/categories" className="block space-y-1 rounded-md p-3">
                          <div className="flex flex-col gap-1 text-sm">
                            <div className="text-sm font-medium">
                              Voir toutes les catégories
                            </div>
                            <p className="text-sm text-muted-foreground">
                              Consultez la liste complète de nos livres classés par catégorie
                            </p>
                          </div>
                        </Link>
                      </NavigationMenuLink>
                    </li>
                    <li>
                      <NavigationMenuLink asChild>
                        <Link href="/publishers" className="block space-y-1 rounded-md p-3">
                          <div className="flex flex-col gap-1 text-sm">
                            <div className="text-sm font-medium">
                              Voir toutes les maisons d'édition
                            </div>
                            <p className="text-sm text-muted-foreground">
                              Consultez la liste complète de nos maisons d'édition
                            </p>
                          </div>
                        </Link>
                      </NavigationMenuLink>
                    </li>
                  </ul>
                </NavigationMenuContent>
              </NavigationMenuItem>
            </NavigationMenuList>
          </NavigationMenu>
        </div>

        <div className="p-6">{children}</div>
      </body>
    </html>
  );
}
