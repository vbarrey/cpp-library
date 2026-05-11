import Link from "next/link"
import { fetchBooks } from "@/lib/api"
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card"

export default async function BooksPage({
  searchParams,
}: {
  searchParams: Promise<{ page?: string }>
}) {
  const params = await searchParams
  const page = Number(params.page || "1")

  const result = await fetchBooks(page)

  console.log(result)

  const totalPages = Math.ceil(result.total / result.limit)

  return (
    <main className="p-6">
      <h1 className="text-xl font-bold mb-4">Livres</h1>

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        {result.data.map((b) => (
          <Card key={b.id} className="overflow-hidden hover:shadow-md transition-shadow">
            <CardContent className="p-4">
              <div className="flex gap-4">
                <img
                  src={b.coverUrl}
                  alt={b.title}
                  className="w-20 h-28 object-cover rounded-md shrink-0"
                />

                <div className="min-w-0 flex-1">
                  <h3 className="font-semibold text-lg truncate">
                    {b.title}
                  </h3>

                  <p className="text-sm text-muted-foreground">
                    {b.author}
                  </p>

                  {b.description && (
                    <p className="text-sm mt-2 line-clamp-3">
                      {b.description}
                    </p>
                  )}
                </div>
              </div>
            </CardContent>
          </Card>
        ))}
      </div>

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