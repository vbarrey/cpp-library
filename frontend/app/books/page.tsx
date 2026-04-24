import Link from "next/link"
import { fetchBooks } from "@/lib/api"

export default async function BooksPage({
  searchParams,
}: {
  searchParams: Promise<{ page?: string }>
}) {
  const params = await searchParams
  const page = Number(params.page || "1")

  const result = await fetchBooks(page)

  const totalPages = Math.ceil(result.total / result.limit)

  return (
    <main className="p-6">
      <h1 className="text-xl font-bold mb-4">Livres</h1>

      <ul className="space-y-2">
        {result.data.map((b) => (
          <li key={b.id} className="border p-3 rounded">
            {b.title} - {b.author}
          </li>
        ))}
      </ul>

      {/* Pagination */}
      <div className="flex gap-2 mt-6">
        {Array.from({ length: totalPages }, (_, i) => (
          <Link
            key={i}
            href={`/books?page=${i + 1}`}
            className={`px-3 py-1 border ${
              page === i + 1 ? "bg-black text-white" : ""
            }`}
          >
            {i + 1}
          </Link>
        ))}
      </div>
    </main>
  )
}