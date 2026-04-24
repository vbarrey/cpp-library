import { fetchBooks } from "@/lib/api"

export default async function Page() {
  const books = await fetchBooks()

  return (
    <main className="p-6">
      <h1 className="text-2xl font-bold mb-4">Library</h1>

      <ul className="space-y-2">
        {books.map((book) => (
          <li key={book.id} className="border p-3 rounded">
            <p className="font-semibold">{book.title}</p>
            <p className="text-sm text-gray-500">{book.author}</p>
          </li>
        ))}
      </ul>
    </main>
  )
}