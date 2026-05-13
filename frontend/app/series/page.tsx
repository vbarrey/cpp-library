import { fetchSeries } from "@/lib/api"
import MediaGrid from "@/components/media/media-grid"
import Link from "next/link"

export default async function SeriesPage({
  searchParams,
}: {
  searchParams: Promise<{ page?: string }>
}) {
  const params = await searchParams
  const page = Number(params.page || "1")

  const result = await fetchSeries(page);

  const totalPages = Math.ceil(result.total / result.limit)
  return (
    <main className="p-6">
      <h1 className="text-xl font-bold mb-4">Séries</h1>
      <MediaGrid medias={result.data} />

      {/* Pagination */}
      <div className="flex gap-2 mt-6">
        {Array.from({ length: totalPages }, (_, i) => (
          <Link
            key={i}
            href={`/series?page=${i + 1}`}
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