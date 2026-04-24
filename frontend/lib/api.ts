export type Book = {
  id: number
  title: string
  author: string
}

const API_URL = process.env.NEXT_PUBLIC_API_URL

export async function fetchBooks(): Promise<Book[]> {
  const res = await fetch(`${API_URL}/books`, { cache: "no-store" });

  if (!res.ok) {
    throw new Error(`Failed to fetch books [${res.status} ${res.statusText}]`)
  }

  return res.json()
}