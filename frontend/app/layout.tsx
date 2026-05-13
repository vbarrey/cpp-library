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
  NavigationMenuTrigger
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
        <div className="flex items-center justify-between sticky top-0 bg-background z-10">
          <div className="flex items-center gap-4">
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
                <NavigationMenuItem>
                  <NavigationMenuTrigger>Jeux</NavigationMenuTrigger>
                  <NavigationMenuContent>
                    <ul className="w-[400px] gap-3 p-4">
                      <li>
                        <NavigationMenuLink asChild>
                          <Link href="/games" className="block space-y-1 rounded-md p-3">
                            <div className="flex flex-col gap-1 text-sm">
                              <div className="text-sm font-medium">
                                Voir tous les jeux
                              </div>
                              <p className="text-sm text-muted-foreground">
                                Consultez la liste complète de nos jeux
                              </p>
                            </div>
                          </Link>
                        </NavigationMenuLink>
                      </li>
                    </ul>
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger>Films</NavigationMenuTrigger>
                  <NavigationMenuContent>
                    <ul className="w-[400px] gap-3 p-4">
                      <li>
                        <NavigationMenuLink asChild>
                          <Link href="/movies" className="block space-y-1 rounded-md p-3">
                            <div className="flex flex-col gap-1 text-sm">
                              <div className="text-sm font-medium">
                                Voir tous les films
                              </div>
                              <p className="text-sm text-muted-foreground">
                                Consultez la liste complète de nos films
                              </p>
                            </div>
                          </Link>
                        </NavigationMenuLink>
                      </li>
                    </ul>
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger>Séries</NavigationMenuTrigger>
                  <NavigationMenuContent>
                    <ul className="w-[400px] gap-3 p-4">
                      <li>
                        <NavigationMenuLink asChild>
                          <Link href="/series" className="block space-y-1 rounded-md p-3">
                            <div className="flex flex-col gap-1 text-sm">
                              <div className="text-sm font-medium">
                                Voir toutes les séries
                              </div>
                              <p className="text-sm text-muted-foreground">
                                Consultez la liste complète de nos séries
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
          <div className="flex justify-end p-4">
            <Link href="/profile" className="flex items-center gap-2">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" strokeWidth={1.5} stroke="currentColor" className="size-6">
                <path strokeLinecap="round" strokeLinejoin="round" d="M17.982 18.725A7.488 7.488 0 0 0 12 15.75a7.488 7.488 0 0 0-5.982 2.975m11.963 0a9 9 0 1 0-11.963 0m11.963 0A8.966 8.966 0 0 1 12 21a8.966 8.966 0 0 1-5.982-2.275M15 9.75a3 3 0 1 1-6 0 3 3 0 0 1 6 0Z" />
              </svg>
              Profile
            </Link>
          </div>
        </div>

        <div className="p-6">{children}</div>
      </body>
    </html>
  );
}
