"use client"

import { useQuery } from "urql"
import { useSearchParams } from "next/navigation"

import {
  GetMoviesDocument
} from "@/graphql/generated/graphql"

import MediaGrid from "@/components/media-grid/media-grid"
import Link from "next/link"

export default function MoviesPage() {
  const searchParams = useSearchParams();

    const page = parseInt(
        searchParams.get("page") || "1"
    );

    const [result] = useQuery({
        query: GetMoviesDocument,

        variables: {
            page
        }
    });

    const { data, fetching, error } = result;

    const totalPages = data && data.movies ? Math.ceil(
      data.movies.total /
      data.movies.limit
    ) : 0;
  return (
    <main className="p-6">
      <h1 className="text-xl font-bold mb-4">Films</h1>

      { fetching && <div>Loading...</div> }
      { error && <div>{error.message}</div> }
      { !fetching && !error && <MediaGrid medias={data?.movies.data || []} /> }

      {/* Pagination */}
      <div className="flex gap-2 mt-6">
        {Array.from({ length: totalPages }, (_, i) => (
          <Link
            key={i}
            href={`/movies?page=${i + 1}`}
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