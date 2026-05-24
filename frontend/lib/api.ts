export type MediaType = "BOOK" | "MOVIE" | "GAME" | "SERIES";

const MEDIA_TYPES: MediaType[] = [
    "BOOK",
    "MOVIE",
    "GAME",
    "SERIES"
];

export function isMediaType(
    value: string
): value is MediaType {
    return MEDIA_TYPES.includes(value as MediaType);
}

export type Genre = {
  id: string,
  name: string,
}

export type Media = {
  id: string,
  type: MediaType,
  title: string,
  description: string,
  coverUrl: string,
  genres: Genre[],
  rating: number,
}

export type Book = Media & {
  author: string
  isbn: string,
  page_count: number,
  publisher: string,
}

export type Movie = Media & {
  director: string
  duration_minutes: number
}

export type Game = Media & {
  developer: string
  platform: string
  multiplayer: boolean
}

export type Series = Media & {
  director: string
  seasons: number
}

export type Paginated<T> = {
  data: T[]
  total: number
  page: number
  limit: number
}

const API_URL = process.env.NEXT_PUBLIC_API_URL

export async function fetchBooks(page: number = 1, limit: number = 84): Promise<Paginated<Book>> {
  const res = await fetch(`${API_URL}/books?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch books [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}

export async function fetchAllGenres(): Promise<Paginated<Genre>> {
  const res = await fetch(`${API_URL}/genres`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch all genres [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}

export async function fetchGenreByMediaType(mediaType:MediaType): Promise<Paginated<Genre>> {
  const res = await fetch(`${API_URL}/genres?mediaType=${mediaType}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch book genres [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}

export async function fetchMovies(page: number = 1, limit: number = 84): Promise<Paginated<Movie>> {
  const res = await fetch(`${API_URL}/movies?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch movies [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}

export async function fetchGames(page: number = 1, limit: number = 84): Promise<Paginated<Game>> {
  const res = await fetch(`${API_URL}/games?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch games [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}

export async function fetchSeries(page: number = 1, limit: number = 84): Promise<Paginated<Series>> {
  const res = await fetch(`${API_URL}/series?page=${page}&limit=${limit}`, { cache: "no-store" });

  if (!res.ok) {
    const error = await res.json();

    throw new Error(`Failed to fetch series [${res.status} ${res.statusText}] : ${error.description}`)
  }

  return res.json()
}