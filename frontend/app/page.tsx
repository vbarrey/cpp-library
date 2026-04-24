import Link from "next/link"

export default function Home() {
  return (
    <main className="p-6">
      <h1 className="text-3xl font-bold mb-4">Cpp Library</h1>

      <p className="mb-6">
        Bienvenue sur ton application de gestion de livres.
      </p>

      <Link
        href="/books"
        className="bg-blue-500 text-white px-4 py-2 rounded"
      >
        Voir les livres
      </Link>
    </main>
  )
}