const API_URL = process.env.BACKEND_API_URL;

export class MovieApiClient {
    async getMovies(page: number = 1) {
        const response = await fetch(
            `${API_URL}/movies?page=${page}`,
            {
                cache: "no-store"
            }
        );

        if (!response.ok) {
            throw new Error("Failed to fetch movies");
        }

        return response.json();
    }

    async getMovie(id: string) {
        const response = await fetch(
            `${API_URL}/movies/${id}`,
            {
                cache: "no-store"
            }
        );

        if (!response.ok) {
            throw new Error("Failed to fetch movie");
        }

        return response.json();
    }
}