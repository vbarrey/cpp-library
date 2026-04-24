export type Book = {
  id: number
  title: string
  author: string
}

export type Paginated<T> = {
  data: T[]
  total: number
  page: number
  limit: number
}

const API_URL = process.env.NEXT_PUBLIC_API_URL

export async function fetchBooks(page: number = 1, limit: number = 20): Promise<Paginated<Book>> {
  const res = await fetch(`${API_URL}/books?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    throw new Error(`Failed to fetch books [${res.status} ${res.statusText}]`)
  }

  console.log(res);

  return res.json()
}