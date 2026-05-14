import { Genre } from "@/lib/api";

export function GenresList({ genres }: { genres: Genre[] }) {
    return (
        <div className="flex gap-2 pt-2">
            {genres && genres.map((genre) => (
                <span 
                    key={genre.id}
                    className="
                    inline-flex 
                    items-center 
                    rounded-md 
                    bg-gray-50
                    px-2 
                    py-1 
                    text-xs 
                    font-medium 
                    text-gray-600 
                    inset-ring 
                    inset-ring-gray-500/10
                ">
                    {genre.name}
                </span>
            ))}
        </div>
    );
}