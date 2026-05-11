export type Book = {
  id: number,
  title: string,
  author: string
  isbn: string,
  page_count: number,
  publisher: string,
  coverUrl: string,
  description: string
}

export type Paginated<T> = {
  data: T[]
  total: number
  page: number
  limit: number
}

const API_URL = process.env.NEXT_PUBLIC_API_URL

export async function fetchBooks(page: number = 1, limit: number = 21): Promise<Paginated<Book>> {
  const res = await fetch(`${API_URL}/books?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch books [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}